/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** unknow_user.c
*/

#include "../../include/client.h"

void unknow_user(char* json_response)
{
    char* user_uuid = json_get_value(json_response, "user_uuid");

    if (user_uuid == NULL) {
        printf("Error: Failed to get user information\n");
        return;
    }

    client_error_unknown_user(user_uuid);

    free(user_uuid);
}
