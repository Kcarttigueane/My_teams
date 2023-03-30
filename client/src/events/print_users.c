/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_users.c
*/

#include "../../include/client.h"

int iterate_users(char* json_str)
{
    char* ptr = strstr(json_str, "\"users\": [");
    if (ptr == NULL) {
        printf("Error: users not found\n");
        return 1;
    }
    ptr += strlen("\"users\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',') {
            ptr++;  // Skip comma separator
        }
        char username[MAX_NAME_LENGTH];
        char user_uuid[MAX_UUID_STR_LEN];
        bool is_logged_in;
        // Extract username
        ptr = strstr(ptr, "\"username\": \"");
        if (ptr == NULL) {
            printf("Error: username not found\n");
            return 1;
        }
        ptr += strlen("\"username\": \"");
        strncpy(username, ptr, MAX_NAME_LENGTH - 1);
        username[strcspn(username, "\"")] = '\0';  // Remove closing quote
        // Extract user_uuid
        ptr = strstr(ptr, "\"user_uuid\": \"");
        if (ptr == NULL) {
            printf("Error: user_uuid not found\n");
            return 1;
        }
        ptr += strlen("\"user_uuid\": \"");
        strncpy(user_uuid, ptr, MAX_UUID_STR_LEN - 1);
        user_uuid[strcspn(user_uuid, "\"")] = '\0';  // Remove closing quote
        // Extract is_logged_in
        ptr = strstr(ptr, "\"is_logged_in\": ");
        if (ptr == NULL) {
            printf("Error: is_logged_in not found\n");
            return 1;
        }
        ptr += strlen("\"is_logged_in\": ");
        if (strncmp(ptr, "true", 4) == 0) {
            is_logged_in = true;
        } else if (strncmp(ptr, "false", 5) == 0) {
            is_logged_in = false;
        } else {
            printf("Error: invalid is_logged_in value\n");
            return 1;
        }
        // Call client_print_users
        printf("user_uuid: %s, user_name: %s, user_status: %d\n", user_uuid,
               username, is_logged_in);
        ptr = strstr(ptr, ",");
    }
    return 0;
}

void print_users(char* json_response)
{
    if (iterate_users(json_response) != 0) {
        printf("Error: failed to iterate users\n");
    }
}
