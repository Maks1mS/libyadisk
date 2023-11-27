//
// Created by maxim on 27.11.23.
//

#include "yadisk_get_disk.h"
#include "yadisk_api_internal.h"

yadisk_code yadisk_get_disk(yadisk_api_client *client, yadisk_disk_info* info) {
    char* output = NULL;
    int error = api_http_request(client, "GET", "/v1/disk", NULL, 0, &output);
    json_object* root = json_tokener_parse(output);
    if (error) {
        json_object_put(root);
        return YADISK_FAILED_PARSE_JSON;
    }

    json_object* total_space = NULL;
    if (!json_object_object_get_ex(root, "total_space", &total_space)) {
        // printf("Key total_space doesn't exists!");
        return YADISK_FAILED_PARSE_JSON;
    }
    info->total_space = json_object_get_uint64(total_space);
    json_object_put(total_space);

    json_object_put(root);
    free(output);
    return YADISK_OK;
}