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

#ifndef YADISK_GET_DISK_RESOURCES_H_INCLUDED
#define YADISK_GET_DISK_RESOURCES_H_INCLUDED

#include "yadisk_shared.h"

#define YADISK_RESOURCE_ITEM_PROPERTIES \
    const char* path; \
    const char* name; \
    const char* resource_id; \
    const char* type; \
    const char* created; \
    const char* modified;

struct yadisk_resource_item {
    YADISK_RESOURCE_ITEM_PROPERTIES
};

typedef struct {
    unsigned long limit;
    unsigned long offset;
    unsigned long total;
} yadisk_resource_embedded;

typedef struct {
    YADISK_RESOURCE_ITEM_PROPERTIES
    const yadisk_resource_embedded* _embedded;
} yadisk_resource_info;

yadisk_code yadisk_get_disk_resources(yadisk_api_client* client, const char* path, yadisk_resource_info* resource);

#endif // YADISK_GET_DISK_RESOURCES_H_INCLUDED
