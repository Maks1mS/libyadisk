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
#include <yadisk.h>
#include <stdio.h>

int main()
{
    char token[1024];

    printf("Enter OAuth token: ");
    fgets(token, sizeof(token), stdin);

    yadisk_init();

    yadisk_api_client* client = &(yadisk_api_client) {
        .token = token
    };

    yadisk_disk_info yadisk_disk_info;
    yadisk_get_disk(client, &yadisk_disk_info);

    printf("Total disk size: %lu\n", yadisk_disk_info.total_space);
    printf("Trash size: %lu\n", yadisk_disk_info.trash_size);
    printf("Used space: %lu\n", yadisk_disk_info.used_space);
    printf("Registration time: %s\n", yadisk_disk_info.reg_time);
    printf("Is paid: %s\n", yadisk_disk_info.is_paid ? "Yes" : "No");

    printf("=================\n");

    yadisk_resource_info resource;
    yadisk_get_disk_resources(client, "/", &resource);
    printf("Path: %s\n", resource.path);
    printf("Name: %s\n", resource.name);
    printf("Type: %s\n", resource.type);
    printf("Created: %s\n", resource.created);
    printf("Modified: %s\n", resource.modified);
    printf("ResourceID: %s\n", resource.resource_id);

    yadisk_cleanup();

    return 0;
}
