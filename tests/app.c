//
// Created by maxim on 27.11.23.
//

#include <yadisk.h>
#include <stdio.h>

int main() {
    char token[1024];

    printf("Enter OAuth token: ");
    fgets(token, sizeof(token), stdin);

    yadisk_api_client* client = &(yadisk_api_client){
            .token = token
    };

    yadisk_disk_info yadisk_disk_info;

    yadisk_get_disk(client, &yadisk_disk_info);

    printf("Total disk size: %lu", yadisk_disk_info.total_space);

    return 0;
}