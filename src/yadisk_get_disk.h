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

#ifndef YADISK_YADISK_GET_DISK_H
#define YADISK_YADISK_GET_DISK_H

#include "yadisk_shared.h"

typedef struct {
    const char* reg_time;
    const char* display_name;
    const char* uid;
    const char* country;
    int is_child;
    const char* login;
} yadisk_user_info;

typedef struct {
    const char* odnoklassniki;
    const char* google;
    const char* instagram;
    const char* vkontakte;
    const char* attach;
    const char* mailru;
    const char* downloads;
    const char* applications;
    const char* facebook;
    const char* social;
    const char* messenger;
    const char* calendar;
    const char* photostream;
    const char* screenshots;
    const char* scans;
} yadisk_system_folders;

typedef struct yadisk_disk_info {
    unsigned long total_space;
    unsigned long trash_size;
    unsigned long used_space;
    int is_paid;
    const char* reg_time;
    yadisk_system_folders system_folders;
    yadisk_user_info user;
    int unlimited_autoupload_enabled;
    unsigned long revision;
} yadisk_disk_info;

yadisk_code yadisk_get_disk(yadisk_api_client* client, yadisk_disk_info* info);

#endif //YADISK_YADISK_GET_DISK_H
