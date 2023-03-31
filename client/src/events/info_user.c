/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** info_user.c
*/

#include "../../include/client.h"

void info_user(char* json_response)
{
    char *username = json_get_value(json_response, "username");
    char *user_uuid = json_get_value(json_response, "user_uuid");
    char *is_logged_in = json_get_value(json_response, "is_logged_in");

    if (username == NULL || user_uuid == NULL || is_logged_in == NULL) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_print_user(user_uuid, username, atoi(is_logged_in));

    free(username);
    free(user_uuid);
    free(is_logged_in);
}
