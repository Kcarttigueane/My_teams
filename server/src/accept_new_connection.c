/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** accept_new_connection.c
*/

#include "../include/server.h"

void accept_new_connection(int server_socket, clients_t clients[MAX_CLIENTS])
{
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    int new_socket = 0;

    if ((new_socket = accept(server_socket, (struct sockaddr*)&address,
        (socklen_t*)&addrlen)) < 0) {
        handle_error("Accept failed");
    }

    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].client_socket_fd == 0) {
            clients[i].client_socket_fd = new_socket;
            printf("New connection, socket fd is %d, ip is : %s, port : %d\n",
            new_socket, inet_ntoa(address.sin_addr),
            ntohs(address.sin_port));
            break;
        }
    }
}
