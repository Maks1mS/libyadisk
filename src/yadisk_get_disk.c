//
// Created by maxim on 27.11.23.
//

#include "yadisk_get_disk.h"
#include "yadisk_api_internal.h"

yadisk_code yadisk_get_disk(yadisk_api_client* client, yadisk_disk_info* info)
{
    char* output = NULL;
    int error = api_http_request(client, "GET", "/v1/disk", NULL, 0, &output);
    if (error) {
        return YADISK_FAILED_HTTP_REQUEST;
    }

    json_object* root = json_tokener_parse(output);
    free(output);

    GET_JSON_UINT64(root, "total_space", &(info->total_space));
    GET_JSON_UINT64(root, "trash_size", &(info->trash_size));
    GET_JSON_UINT64(root, "used_space", &(info->used_space));
    GET_JSON_STRING(root, "reg_time", &(info->reg_time));
    GET_JSON_BOOL(root, "is_paid", &(info->is_paid));

    json_object_put(root);


    return YADISK_OK;
}
