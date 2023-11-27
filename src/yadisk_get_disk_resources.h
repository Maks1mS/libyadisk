//
// Created by maxim on 27.11.23.
//
#include "yadisk_shared.h"

typedef struct {
} yadisk_resource_embedded;

typedef struct
{
    const char* path;
    const char* name;
    const char* resource_id;
    const char* type;
    const yadisk_resource_embedded* _embedded;
} yadisk_resource_info;

yadisk_code yadisk_get_disk_resources(yadisk_api_client *client, const char *path);