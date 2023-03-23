/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** client
*/

#include "../include/client.h"

int client_engine(client_t* client, char* ip, int port)
{
    init_socket(client);
    init_addresses(client, ip, port);
    connection(client);

    while (true) {
        // manage_command(client);
    }

    close(client->socket);
    return 0;
}
