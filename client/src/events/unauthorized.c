/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** unauthorized.c
*/

#include "../../include/client.h"

void unauthorized(char *json_response)
{
    (void)json_response;
    client_error_unauthorized();
}
