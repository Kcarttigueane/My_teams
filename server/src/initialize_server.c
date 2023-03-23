/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** initialize_server.c
*/

#include "../include/server.h"

int bind_and_listen_socket(server_data_t* s)
{
    struct sockaddr_in server_address;
    int addrlen = sizeof(server_address);

    memset(&server_address, 0, addrlen);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(s->PORT);

    if (bind(s->socket_fd, (struct sockaddr*)&server_address, addrlen) < 0)
        return handle_error("Bind failed");

    if (listen(s->socket_fd, 3) < 0)
        return handle_error("Listen failed");

    return 0;
}

int initialize_server(server_data_t* s)
{
    if ((s->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == FAILURE)
        return handle_error("Socket creation failed");

    size_t opt = 1;
    if (setsockopt(s->socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        return handle_error("setsockopt failed");

    if (bind_and_listen_socket(s) == ERROR)
        return handle_error("Bind and listen failed");

    return 0;
}
