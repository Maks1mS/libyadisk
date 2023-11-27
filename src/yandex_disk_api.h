//
// Created by maxim on 26.11.23.
//

#ifndef YANDEX_DISK_API_H
#define YANDEX_DISK_API_H

#include <string.h>
#include <ne_session.h>
#include <ne_request.h>
#include <ne_ssl.h>

typedef struct yadisk_api_client
{
    char* token;
} yadisk_api_client;

typedef struct yadisk_disk_info
{
    unsigned long total_space;
} yadisk_disk_info;

void yadisk_get_disk(yadisk_api_client* client, yadisk_disk_info* info);
void yadisk_delete_disk_resources(yadisk_api_client *client);

#endif //YANDEX_DISK_API_H
