//
// Created by maxim on 27.11.23.
//

#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json.h>
#include "yadisk_shared.h"
#include "yadisk_api_internal.h"

struct memory {
    char *response;
    size_t size;
};

// Callback function for writing response data
static size_t write_callback(void *contents, size_t size, size_t nmemb, struct memory *mem) {
    size_t realsize = size * nmemb;
    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(!ptr) {
        // out of memory
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

// Function to make an HTTP request using libcurl
int api_http_request(
        yadisk_api_client *client,
        const char* method,
        const char* path,
        query_param *params,
        size_t num_params,
        char** output
        ) {
    CURL *curl;
    CURLcode res;
    struct memory chunk = {0};

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        char url[256];
        snprintf(url, sizeof(url), "%s%s", YANDEX_DISK_API_HOST, path);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // Set the HTTP method
        if (strcmp(method, "GET") == 0) {
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        } else if (strcmp(method, "POST") == 0) {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
        } else if (strcmp(method, "DELETE") == 0) {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        } else if (strcmp(method, "PATCH") == 0) {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
        }

        // Set the authorization header
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: OAuth %s", client->token);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, auth_header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(chunk.response);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return -1;
        } else {
            *output = strdup(chunk.response);
        }

        // Clean up
        curl_slist_free_all(headers);
        free(chunk.response);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
