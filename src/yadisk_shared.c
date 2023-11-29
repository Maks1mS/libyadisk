//
// Created by maxim on 27.11.23.
//

#include "yadisk_shared.h"

int yadisk_init()
{
    return curl_global_init(CURL_GLOBAL_ALL);
}

void yadisk_cleanup()
{
    curl_global_cleanup();
}