/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** client
*/

#include "../include/client.h"

volatile sig_atomic_t stop_server = false;

static int handle_inputs(client_data_t* client)
{
    if (FD_ISSET(STDIN_FILENO, &client->read_fds)) {
        if (handle_user_input(client) == ERROR) {
            return handle_error("Failed to handle user input.");
        }
    }
    if (FD_ISSET(client->socket_fd, &client->read_fds)) {
        char buffer[BUFFER_SIZE] = {0};
        if (handle_server_input(client, buffer) == ERROR) {
            return handle_error("Failed to handle server input.");
        }
    }
    return SUCCESS;
}

int client_loop(client_data_t* client)
{
    struct timeval tv = {.tv_sec = DEFAULT_TIMEOUT, .tv_usec = 0};

    while (!stop_server) {
        FD_ZERO(&client->read_fds);
        FD_SET(STDIN_FILENO, &client->read_fds);
        FD_SET(client->socket_fd, &client->read_fds);

        if ((select(client->socket_fd + 1, &client->read_fds, NULL, NULL,
            &tv) == FAILURE) && (errno != EINTR)) {
            handle_error("Select failed");
        }
        if (stop_server) break;

        if (handle_inputs(client) == ERROR)
            return handle_error("Failed to handle inputs.");
    }
    printf("Closing connection.\n");
    close(client->socket_fd);
    return 0;
}
