/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** init_client
*/

#include "../include/client.h"

int init_socket(client_t* client)
{
    if ((client->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // error: socket can't be created
        return -1;
    }
    return 0;
}

int init_addresses(client_t* client, char* ip, int port)
{
    int status = 0;

    client->serv_addr.sin_family = AF_INET;
    client->serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &client->serv_addr.sin_addr) <= 0) {
        // error: invalid address / not supported
        return -1;
    }
    return 0;
}

int connection(client_t* client)
{
    int status = 0;

    if ((status = connect(client->socket, (struct sockaddr*)&client->serv_addr,
                          sizeof(client->serv_addr))) < 0) {
        // error: connection failed
        return -1;
    }
    return 0;
}
