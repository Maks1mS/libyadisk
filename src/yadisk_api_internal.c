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
    char* response;
    size_t size;
};

struct data {
    char trace_ascii; /* 1 or 0 */
};


static size_t cb(void* data, size_t size, size_t nmemb, void* clientp)
{
    size_t realsize = size * nmemb;
    struct memory* mem = (struct memory*)clientp;

    char* ptr = realloc(mem->response, mem->size + realsize + 1);
    if (ptr == NULL)
        return 0;  /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

char* build_query_string(query_param* params, size_t num_params)
{
    CURL* curl = curl_easy_init();
    if (!curl) {
        return NULL;
    }

    char* query = NULL;
    size_t query_len = 0;

    for (size_t i = 0; i < num_params; ++i) {
        char* encoded_key = curl_easy_escape(curl, params[i].key, 0);
        char* encoded_value = curl_easy_escape(curl, params[i].value, 0);

        // Calculate additional space needed: key=value& (including null terminator)
        size_t additional_len = strlen(encoded_key) + strlen(encoded_value) + 2;
        if (i < num_params - 1) {
            additional_len++; // For '&'
        }

        query = realloc(query, query_len + additional_len);
        sprintf(query + query_len, "%s=%s", encoded_key, encoded_value);
        query_len += additional_len - 1; // Minus null terminator

        if (i < num_params - 1) {
            strcat(query, "&");
        }

        curl_free(encoded_key);
        curl_free(encoded_value);
    }

    curl_easy_cleanup(curl);
    return query;
}

// Function to make an HTTP request using libcurl
int api_http_request(
    yadisk_api_client* client,
    const char* method,
    const char* path,
    query_param* params,
    size_t num_params,
    char** output
)
{
    CURL* curl;
    CURLcode res;
    struct memory chunk = {0};

    curl = curl_easy_init();

    if (curl) {
        char url[512];
        if (num_params) {
            char* query_string = build_query_string(params, num_params);
            snprintf(url, sizeof(url), "%s%s?%s", YANDEX_DISK_API_HOST, path, query_string);
            free(query_string);
        } else {
            snprintf(url, sizeof(url), "%s%s", YANDEX_DISK_API_HOST, path);
        }
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

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
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, auth_header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(chunk.response);
            curl_easy_cleanup(curl);
            return -1;
        } else {
            *output = strdup(chunk.response);
        }

        // Clean up
        curl_slist_free_all(headers);
        free(chunk.response);
        curl_easy_cleanup(curl);
    }

    return 0;
}
