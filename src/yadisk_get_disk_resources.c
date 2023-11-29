//
// Created by maxim on 27.11.23.
//
#include "yadisk_get_disk_resources.h"
#include "yadisk_api_internal.h"

yadisk_code
yadisk_get_disk_resources(
    yadisk_api_client* client, const char* path, yadisk_resource_info* info
)
{
    char* output = NULL;
    query_param params[] = {
        {"path", path},
    };
    int error = api_http_request(client, "GET", "/v1/disk/resources", params, 1, &output);
    if (error) {
        return YADISK_FAILED_HTTP_REQUEST;
    }
    json_object* root = json_tokener_parse(output);
    free(output);
    GET_JSON_STRING(root, "path", &(info->path));
    GET_JSON_STRING(root, "name", &(info->name));
    GET_JSON_STRING(root, "resource_id", &(info->resource_id));
    GET_JSON_STRING(root, "type", &(info->type));
    GET_JSON_STRING(root, "created", &(info->created));
    GET_JSON_STRING(root, "modified", &(info->modified));

    json_object_put(root);
    return YADISK_OK;
};
