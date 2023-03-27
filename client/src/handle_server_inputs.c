/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** handle_server_inputs.c
*/

#include "../include/client.h"

int handle_server_input(client_data_t* client, char* buffer)
{
    ssize_t bytes_received = recv(client->socket_fd, buffer, BUFFER_SIZE, 0);

    if (bytes_received <= 0) {
        fprintf(stderr, "Server closed connection.\n");
        return FAILURE;
    }

    printf("Received from server:\n");
    printf("\033[0;33m");
    printf("%s", buffer);
    printf("\033[0m");

    printf("Received from server: %s", buffer);
    return SUCCESS;
}
