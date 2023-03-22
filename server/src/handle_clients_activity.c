/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** get_max_socket_descriptor.c
*/

#include "../include/server.h"

void handle_client_activity(clients_t clients[MAX_CLIENTS], server_data_t* s)
{
    char buffer[BUFFER_SIZE] = {0};

    for (int i = 0; i < MAX_CLIENTS; i++) {
        int sd = clients[i].client_socket_fd;
        // Check if the file descriptor is ready for reading
        if (FD_ISSET(sd, &s->readfds)) {
            int bytes_read;
            if ((bytes_read = read(sd, buffer, BUFFER_SIZE)) == 0) {
                close(sd);
                clients[i].client_socket_fd = 0;
                printf("Client disconnected, socket fd is %d\n", sd);
            } else {
                buffer[bytes_read] = '\0';
                printf("Received data from client: %s", buffer);
                write(sd, buffer, strlen(buffer));
            }
        }
    }
}
