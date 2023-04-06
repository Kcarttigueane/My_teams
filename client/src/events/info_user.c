/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** info_user.c
*/

#include "../../include/client.h"

void info_user(char* json_response)
{
    char username[MAX_NAME_LENGTH] = {0};
    char user_uuid[MAX_UUID_LENGTH] = {0};
    bool is_logged_in = false;

    if (!extract_value("username", json_response, username, sizeof(username)) ||
        !extract_value("user_uuid", json_response, user_uuid,
        sizeof(user_uuid)) ||
        !extract_boolean_value("is_logged_in", json_response, &is_logged_in)) {
        printf("Error: invalid JSON format\n");
        return;
    }
    client_print_user(user_uuid, username, is_logged_in);
}
