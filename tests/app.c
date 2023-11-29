//
// Created by maxim on 27.11.23.
//

#include <yadisk.h>
#include <stdio.h>

int main() {
    char token[1024];

    printf("Enter OAuth token: ");
    fgets(token, sizeof(token), stdin);

    yadisk_init();

    yadisk_api_client* client = &(yadisk_api_client){
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
