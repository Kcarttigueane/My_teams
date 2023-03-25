/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** handle_client_inputs.c
*/

#include "../include/client.h"

int handle_user_input(client_data_t* client)
{
    char buffer[BUFFER_SIZE] = {0};

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        return SUCCESS;
    }
    size_t len = strcspn(buffer, "\n");
    buffer[len] = '\0';

    send(client->socket_fd, buffer, strlen(buffer), 0);

    return SUCCESS;
}
