/*
 * libyadisk - A C library for interacting with Yandex.Disk API
 *
 * Copyright (C) 2023 Maxim Slipenko
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
 */

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
