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

#ifndef YADISK_YADISK_API_INTERNAL_H
#define YADISK_YADISK_API_INTERNAL_H

#define YANDEX_DISK_API_HOST "https://cloud-api.yandex.net"

typedef struct {
    const char* key;
    const char* value;
} query_param;

int api_http_request(yadisk_api_client* client,
                     const char* method,
                     const char* path,
                     query_param* params,
                     size_t num_params,
                     char** output);


#define THROW_PARSE_JSON_ERROR { \
        return YADISK_FAILED_PARSE_JSON; \
    }

#define __DANGER_GET_JSON_OBJECT(root, key)          \
    json_object* obj = NULL;                         \
    if (!json_object_object_get_ex(root, key, &obj)){\
        json_object_put(root);                       \
        THROW_PARSE_JSON_ERROR                       \
    }                                                \

#define GET_JSON_STRING(root, key, v) {              \
        __DANGER_GET_JSON_OBJECT(root, key)              \
        *v = json_object_get_string(obj);                \
    }

#define GET_JSON_UINT64(root, key, v) {              \
        __DANGER_GET_JSON_OBJECT(root, key)              \
        *v = json_object_get_uint64(obj);                \
    }
#define GET_JSON_BOOL(root, key, v) {                \
        __DANGER_GET_JSON_OBJECT(root, key)              \
        *v = json_object_get_boolean(obj);               \
    }

#endif //YADISK_YADISK_API_INTERNAL_H
