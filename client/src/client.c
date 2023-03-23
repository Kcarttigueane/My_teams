/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** client
*/

#include "../include/client.h"

void select_socket(client_data_t *client)
{
    client->activity =
        select(client->socket_fd + 1, &client->read_fds, NULL, NULL, NULL);

    if ((client->activity < 0) && (errno != EINTR)) {
        handle_error("error: select failed");
    }
}

int client_loop(client_data_t *client)
{
    while (true) {
        FD_ZERO(&client->read_fds);
        FD_SET(client->socket_fd, &client->read_fds);
        select_socket(client);
        // TO DO : read
    }

    close(client->socket_fd);
    return 0;
}
