/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** server_loop.c
*/

#include "../include/server.h"

static void add_client_socket_to_set(clients_t clients[MAX_CLIENTS],
server_data_t* s)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        int sd = clients[i].client_socket_fd;
        if (sd > 0)
            FD_SET(sd, &s->readfds);
    }
}

int get_max_socket_descriptor(clients_t clients[MAX_CLIENTS], int server_socket)
{
    int max_socket_descriptor = server_socket;

    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        int sd = clients[i].client_socket_fd;

        if (sd > 0 && sd > max_socket_descriptor)
            max_socket_descriptor = sd;
    }
    return (max_socket_descriptor + 1);
}

void server_loop(server_data_t* s)
{
    clients_t clients[MAX_CLIENTS] = {0};
    struct timeval tv = {.tv_sec = 5, .tv_usec = 0};

    while (true) {
        FD_ZERO(&s->readfds);
        FD_SET(s->socket_fd, &s->readfds);

        add_client_socket_to_set(clients, s);

        if ((select(get_max_socket_descriptor(clients, s->socket_fd),
            &s->readfds, NULL, NULL, &tv) == FAILURE) && (errno != EINTR)) {
            handle_error("Select failed");
        }

        if (FD_ISSET(s->socket_fd, &s->readfds))
            accept_new_connection(s->socket_fd, clients);

        handle_client_activity(clients, s);
    }
}