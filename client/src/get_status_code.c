/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** get_status_code.c
*/

#include "../include/client.h"

int get_status_code(const char* json_string)
{
    int status_code = 0;
    const char* status_field = strstr(json_string, "\"status\": ");

    if (status_field != NULL)
        sscanf(status_field, "\"status\": %d,", &status_code);

    return status_code;
}
