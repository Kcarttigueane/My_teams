/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** init_client
*/

#include "../include/client.h"

static int init_socket(client_data_t *client)
{
    if ((client->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == FAILURE)
        return handle_error("error: socket can't be created");
    return 0;
}

static int init_addresses(client_data_t *client)
{
    memset(&client->serv_addr, 0, sizeof(client->serv_addr));

    client->serv_addr.sin_family = AF_INET;
    client->serv_addr.sin_port = htons(client->port);

    if (inet_pton(AF_INET, client->ip, &client->serv_addr.sin_addr) <= 0)
        return handle_error("error: invalid address / not supported");
    return 0;
}

static int connect_to_server(client_data_t *client)
{
    int status = 0;

    if ((status = connect(client->socket_fd, (struct sockaddr *)&client->serv_addr,
            sizeof(client->serv_addr))) < 0)
        return handle_error("error: connection failed");
    return 0;
}

int init_client(client_data_t *client)
{
    if (init_socket(client) == ERROR)
        return ERROR;
    if (init_addresses(client) == ERROR)
        return ERROR;
    if (connect_to_server(client) == ERROR)
        return ERROR;
    return 0;
}
