/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** connection_successful.c
*/

#include "../../include/client.h"

void connection_successful(char* json_resp)
{
    char username[MAX_NAME_LENGTH] = {0};
    char user_uuid[MAX_UUID_LENGTH] = {0};

    if (!extract_value("username", json_resp, username, sizeof(username)) ||
        !extract_value("user_uuid", json_resp, user_uuid, sizeof(user_uuid))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_event_logged_in(user_uuid, username);
}
