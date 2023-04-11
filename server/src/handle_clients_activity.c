/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** get_max_socket_descriptor.c
*/

#include "../include/server.h"

static void clear_disconnected_client(clients_t* client)
{
    client->socket_fd = 0;
    client->is_logged = false;

    client->current_user_uuid[0] = '\0';
    client->current_team_uuid[0] = '\0';
    client->current_channel_uuid[0] = '\0';
    client->current_thread_uuid[0] = '\0';

    client->use_args_count = FAILURE;
}

static void handle_client_disconnected(int socket_fd, clients_t* client)
{
    close(socket_fd);
    clear_disconnected_client(client);
    printf("Client disconnected, socket fd is %d\n", socket_fd);
}

static void handle_received_data(list_args_t* args, char* buffer)
{
    buffer[strlen(buffer)] = '\0';
    parse_client_input(args, buffer);
}

void handle_client_activity(clients_t* clients, server_data_t* s,
database_t* db)
{
    char buffer[BUFFER_SIZE] = {0};

    for (int i = 0; i < MAX_CLIENTS; i++) {
        int sd = clients[i].socket_fd;

        if (FD_ISSET(sd, &s->readfds)) {
            list_args_t args = {
                .server_data = s,
                .split_command = NULL,
                .client = &clients[i],
                .db = db,
                .clients = clients
            };
            int bytes_read = read(sd, buffer, BUFFER_SIZE);
            (bytes_read == 0)
                ? handle_client_disconnected(sd, &clients[i])
                : handle_received_data(&args, buffer);
        }
    }
}
