/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_users.c
*/

#include "../../include/client.h"

static bool user_parsing(char* ptr)
{
    char user_uuid[MAX_UUID_LENGTH] = {0};
    char username[MAX_NAME_LENGTH] = {0};
    bool is_logged_in;

    extract_value("user_uuid", ptr, user_uuid, MAX_UUID_LENGTH);
    extract_value("username", ptr, username, MAX_NAME_LENGTH);
    extract_boolean_value("is_logged_in", ptr, &is_logged_in);

    if (!(*user_uuid != '\0' && *username != '\0'))
        return false;

    client_print_users(user_uuid, username, is_logged_in);

    return true;
}

void print_users(char* json_response)
{
    char* ptr = strstr(json_response, "\"users\": [");

    if (!ptr) {
        printf("Error: users not found\n");
        return;
    }

    ptr += strlen("\"users\": [");

    while (ptr != NULL && *ptr != ']') {
        if (*ptr == ',')
            ptr++;
        if (!user_parsing(ptr))
            break;
        ptr = strstr(ptr, "},");
        if (ptr != NULL)
            ptr += 2;
    }
}
