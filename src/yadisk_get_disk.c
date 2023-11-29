/*
 * libyadisk - A C library for interacting with Yandex.Disk API
 *
 * This file is part of libyadisk.
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
