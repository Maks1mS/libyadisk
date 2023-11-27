//
// Created by maxim on 27.11.23.
//

#ifndef YADISK_YADISK_GET_DISK_H
#define YADISK_YADISK_GET_DISK_H

#include "yadisk_shared.h"

typedef struct yadisk_disk_info
{
    unsigned long total_space;
} yadisk_disk_info;

yadisk_code yadisk_get_disk(yadisk_api_client *client, yadisk_disk_info* info);

#endif //YADISK_YADISK_GET_DISK_H
