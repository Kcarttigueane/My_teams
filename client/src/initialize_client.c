/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** init_client
*/

#include "../include/client.h"

int connect_to_server(const char* server_address, int port)
{
    int socket_fd;
    struct sockaddr_in server_addr;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return handle_error("Socket creation failed");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_address, &server_addr.sin_addr) <= 0)
        return handle_error("Invalid address or unsupported address family");

    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        return handle_error("Connection failed");

    return socket_fd;
}
