//
// Created by maxim on 27.11.23.
//

#ifndef YADISK_YADISK_SHARED_H
#define YADISK_YADISK_SHARED_H

#include <stddef.h>
#include <curl/curl.h>
#include <json.h>

typedef enum {
    YADISK_OK = 0,
    YADISK_FAILED_PARSE_JSON = 1
} yadisk_code;

typedef struct {
    char* token;
} yadisk_api_client;

#endif //YADISK_YADISK_SHARED_H
