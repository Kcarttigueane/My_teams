/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** unknow_user.c
*/

#include "../../include/client.h"

void unknow_user(char* json_response)
{
    char user_uuid[MAX_UUID_LENGTH] = {0};

    if (!extract_value("user_uuid", json_response, user_uuid,
        sizeof(user_uuid))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_error_unknown_user(user_uuid);
}
