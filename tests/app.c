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

    yadisk_disk_info info;
    yadisk_get_disk(client, &info);

    printf("Total disk size: %lu\n", info.total_space);
    printf("Trash size: %lu\n", info.trash_size);
    printf("Used space: %lu\n", info.used_space);
    printf("Registration time: %s\n", info.reg_time);
    printf("Is paid: %s\n", info.is_paid ? "Yes" : "No");

    printf("User Info:\n");
    printf("  Registration time: %s\n", info.user.reg_time);
    printf("  Display Name: %s\n", info.user.display_name);
    printf("  UID: %s\n", info.user.uid);
    printf("  Country: %s\n", info.user.country);
    printf("  Is Child: %s\n", info.user.is_child ? "Yes" : "No");
    printf("  Login: %s\n", info.user.login);

    printf("System Folders:\n");
    printf("  Odnoklassniki: %s\n", info.system_folders.odnoklassniki);
    printf("  Google: %s\n", info.system_folders.google);
    printf("  Instagram: %s\n", info.system_folders.instagram);
    printf("  Vkontakte: %s\n", info.system_folders.vkontakte);
    printf("  Attach: %s\n", info.system_folders.attach);
    printf("  Mailru: %s\n", info.system_folders.mailru);
    printf("  Downloads: %s\n", info.system_folders.downloads);
    printf("  Applications: %s\n", info.system_folders.applications);
    printf("  Facebook: %s\n", info.system_folders.facebook);
    printf("  Social: %s\n", info.system_folders.social);
    printf("  Messenger: %s\n", info.system_folders.messenger);
    printf("  Calendar: %s\n", info.system_folders.calendar);
    printf("  Photostream: %s\n", info.system_folders.photostream);
    printf("  Screenshots: %s\n", info.system_folders.screenshots);
    printf("  Scans: %s\n", info.system_folders.scans);

    printf("Unlimited Autoupload Enabled: %s\n", info.unlimited_autoupload_enabled ? "Yes" : "No");
    printf("Revision: %lu\n", info.revision);

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
