/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** send_json_error_response.c
*/

#include "../include/lib.h"

void send_json_error_response(int socket_fd, int status_code,
const char* error_message)
{
    char* json_error_resp =
        "{\n"
        "  \"status\": %d,\n"
        "  \"error\": \"%s\"\n"
        "}\n";

    dprintf(socket_fd, json_error_resp, status_code, error_message);
}
