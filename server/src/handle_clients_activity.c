/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** get_max_socket_descriptor.c
*/

#include "../include/server.h"

static void handle_client_disconnected(int socket_fd, clients_t* client)
{
    close(socket_fd);
    client->socket_fd = 0;
    // ! NEED TO SHIFT ALL THE CLIENTS AFTER THIS ONE
    printf("Client disconnected, socket fd is %d\n", socket_fd);
}

static void handle_received_data(char* buffer, clients_t* client,
server_data_t* s, database_t* db)
{
    buffer[strlen(buffer)] = '\0';
    printf("Received data from client: %s\n", buffer);
    parse_client_input(client, s, buffer, db);
}

void handle_client_activity(clients_t* clients, server_data_t* s,
database_t* db)
{
    char buffer[BUFFER_SIZE] = {0};

    for (int i = 0; i < MAX_CLIENTS; i++) {
        int sd = clients[i].socket_fd;

        if (FD_ISSET(sd, &s->readfds)) {
            int bytes_read = read(sd, buffer, BUFFER_SIZE);
            (bytes_read == 0)
                ? handle_client_disconnected(sd, &clients[i])
                : handle_received_data(buffer, &clients[i], s, db);
        }
    }
}
