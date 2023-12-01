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

    json_object *user_object;
    if (!json_object_object_get_ex(root, "user", &user_object))
        THROW_PARSE_JSON_ERROR

    GET_JSON_STRING(user_object, "reg_time", &(info->user.reg_time));
    GET_JSON_STRING(user_object, "display_name", &(info->user.display_name));
    GET_JSON_STRING(user_object, "uid", &(info->user.uid));
    GET_JSON_STRING(user_object, "country", &(info->user.country));
    GET_JSON_BOOL(user_object, "is_child", &(info->user.is_child));
    GET_JSON_STRING(user_object, "login", &(info->user.login));

    json_object *system_folders;
    if (!json_object_object_get_ex(root, "system_folders", &system_folders))
        THROW_PARSE_JSON_ERROR

    GET_JSON_STRING(system_folders, "odnoklassniki", &(info->system_folders.odnoklassniki));
    GET_JSON_STRING(system_folders, "google", &(info->system_folders.google));
    GET_JSON_STRING(system_folders, "instagram", &(info->system_folders.instagram));
    GET_JSON_STRING(system_folders, "vkontakte", &(info->system_folders.vkontakte));
    GET_JSON_STRING(system_folders, "attach", &(info->system_folders.attach));
    GET_JSON_STRING(system_folders, "mailru", &(info->system_folders.mailru));
    GET_JSON_STRING(system_folders, "downloads", &(info->system_folders.downloads));
    GET_JSON_STRING(system_folders, "applications", &(info->system_folders.applications));
    GET_JSON_STRING(system_folders, "facebook", &(info->system_folders.facebook));
    GET_JSON_STRING(system_folders, "social", &(info->system_folders.social));
    GET_JSON_STRING(system_folders, "messenger", &(info->system_folders.messenger));
    GET_JSON_STRING(system_folders, "calendar", &(info->system_folders.calendar));
    GET_JSON_STRING(system_folders, "photostream", &(info->system_folders.photostream));
    GET_JSON_STRING(system_folders, "screenshots", &(info->system_folders.screenshots));
    GET_JSON_STRING(system_folders, "scans", &(info->system_folders.scans));

    GET_JSON_BOOL(root, "unlimited_autoupload_enabled", &(info->unlimited_autoupload_enabled));
    GET_JSON_UINT64(root, "revision", &(info->revision));

    json_object_put(root);


    return YADISK_OK;
}
