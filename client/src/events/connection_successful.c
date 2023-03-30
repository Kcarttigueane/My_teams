/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** connection_successful.c
*/

#include "../../include/client.h"

void connection_successful(char* json_response)
{
    char* username = json_get_value(json_response, "username");
    char* user_uuid = json_get_value(json_response, "user_uuid");

    if (username == NULL || user_uuid == NULL) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_event_logged_in(user_uuid, username);

    free(user_uuid);
    free(username);
}
