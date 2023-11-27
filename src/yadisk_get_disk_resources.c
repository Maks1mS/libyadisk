//
// Created by maxim on 27.11.23.
//
#include "yadisk_get_disk_resources.h"
#include "yadisk_api_internal.h"

yadisk_code
yadisk_get_disk_resources(yadisk_api_client *client, const char *path) {
    char *output;
    int error = api_http_request(client, "GET", "/v1/disk", NULL, 0, &output);
};