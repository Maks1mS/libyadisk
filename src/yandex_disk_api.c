//
// Created by maxim on 26.11.23.
//

#include "yandex_disk_api.h"
#include "json.h"

#define YANDEX_DISK_API_HOST "cloud-api.yandex.net"

static int ssl_verify_callback(void *userdata, int failures, const ne_ssl_certificate *cert);
static int api_http_request(
        yadisk_api_client *client,
            const char* method,
            const char* path,
            char** output
            );

void yadisk_get_disk(yadisk_api_client *client, yadisk_disk_info* info) {
    char* output = NULL;
    int error = api_http_request(client, "GET", "/v1/disk", &output);
    json_object* root = json_tokener_parse(output);

    if (error) {
        json_object_put(root);
        return;
    }

    json_object* total_space = NULL;
    if (!json_object_object_get_ex(root, "total_space", &total_space)) {
        printf("Key total_space doesn't exists!");
    }
    info->total_space = json_object_get_uint64(total_space);
    json_object_put(total_space);

    json_object_put(root);
    free(output);
}

void yadisk_delete_disk_resources(yadisk_api_client *client) {
    char* output = NULL;
    int result = api_http_request(client, "DELETE", "/v1/disk/resource", &output);

    if (!result) {
        // error
    }

    free(output);
}

static int ssl_verify_callback(void *userdata, int failures, const ne_ssl_certificate *cert) {
    if (failures & NE_SSL_UNTRUSTED) {
        return 0;
    }
    return 1;
};

static void
set_api_auth_header(
        ne_request *req,
        yadisk_api_client* client
) {
    size_t str_size = 6 + strlen(client->token) + 1;
    char *str = malloc(sizeof(char) * str_size);
    snprintf(str, str_size, "OAuth %s", client->token);
    ne_add_request_header(req, "Authorization", str);
}

static int
api_http_request(
        yadisk_api_client* client,
        const char* method,
        const char* path,
        char** output
        )
{
    ne_session *sess;
    ne_request *req;
    sess = ne_session_create("https", YANDEX_DISK_API_HOST, 443);
    ne_ssl_set_verify(sess, ssl_verify_callback, NULL);

    req = ne_request_create(sess, method, path);

    set_api_auth_header(req, client);

    char* result = malloc(1);
    size_t currentSize = 1;  // Текущий размер буфера result

    do {
        int stat = ne_begin_request(req);
        const ne_status* status = ne_get_status(req);

        if (stat != NE_OK) {
            if (!status->code) {
                return -1;
            }
            return -1;
        }

        if (status->code != 200) {
            return -2;
        }

        char buffer[1024];
        ssize_t bytes;  // Количество прочитанных байт

        while ((bytes = ne_read_response_block(req, buffer, 1024)) > 0) {
            currentSize += bytes;
            result = realloc(result, currentSize);
            strncat(result, buffer, bytes);
        }
    } while (ne_end_request(req));

    ne_request_destroy(req);
    ne_session_destroy(sess);
    ne_sock_exit();

    *output = malloc(currentSize * sizeof(char));
    strcpy(*output, result);
    free(result);

    return 0;
}