/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_users.c
*/

#include "../../include/client.h"

static void extract_user_info(char* ptr, char* user_uuid, char* username,
bool* is_logged_in)
{
    extract_value("user_uuid", ptr, user_uuid, MAX_UUID_LENGTH);
    extract_value("username", ptr, username, MAX_NAME_LENGTH);
    extract_boolean_value("is_logged_in", ptr, is_logged_in);
}

static bool is_user_info_valid(char* user_uuid, char* username)
{
    return *user_uuid != '\0' && *username != '\0';
}

void print_users(char* json_response)
{
    char* ptr = strstr(json_response, "\"users\": [");

    if (ptr == NULL) {
        printf("Error: users not found\n");
        return;
    }

    ptr += strlen("\"users\": [");
    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',') ptr++;
        char user_uuid[MAX_UUID_LENGTH] = {0};
        char username[MAX_NAME_LENGTH] = {0};
        bool is_logged_in;
        extract_user_info(ptr, user_uuid, username, &is_logged_in);
        if (!is_user_info_valid(user_uuid, username)) break;
        client_print_users(user_uuid, username, is_logged_in);
        ptr = strstr(ptr, "},");
        if (ptr != NULL) ptr += 2;
    }
}
