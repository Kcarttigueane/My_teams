/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** client
*/

#include "../include/client.h"

int select_socket(client_data_t* client)
{
    if (select(client->socket_fd + 1, &client->read_fds, NULL, NULL, NULL) <
    0 && errno != EINTR) {
        return handle_error("Select failed");
    }
    return 0;
}

int client_loop(client_data_t* client)
{
    char buffer[BUFFER_SIZE] = {0};

    while (true) {
        FD_ZERO(&client->read_fds);
        FD_SET(client->socket_fd, &client->read_fds);

        if (select_socket(client) == ERROR)
            return ERROR;

        // TODO: read
    }

    close(client->socket_fd);
    return 0;
}
