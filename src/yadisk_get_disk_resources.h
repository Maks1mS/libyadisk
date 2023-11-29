//
// Created by maxim on 27.11.23.
//
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
