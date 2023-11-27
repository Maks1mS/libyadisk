//
// Created by maxim on 27.11.23.
//

#ifndef YADISK_YADISK_API_INTERNAL_H
#define YADISK_YADISK_API_INTERNAL_H

#define YANDEX_DISK_API_HOST "https://cloud-api.yandex.net"

typedef struct {
    const char *key;
    const char *value;
} query_param;

int api_http_request(yadisk_api_client *client,
                     const char *method,
                     const char *path,
                     query_param *params,
                     size_t num_params,
                     char **output);

#endif //YADISK_YADISK_API_INTERNAL_H
