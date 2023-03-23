/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

    // ! My includes:

    #include "../../include/my_teams.h"
    #include "../../include/lib.h"

    #define CLIENT_USAGE                 \
        "USAGE: ./myteams_cli ip port\n\
            \tip is the server ip address on which the server socket listens\n\
            \tport is the port number on which the server socket listens\n"

#define BUFFER_SIZE 4096

extern char *command_list[];

typedef struct client {
    int socket;
    struct sockaddr_in serv_addr;
} client_t;

//  init client

int init_socket(client_t* client);
int init_addresses(client_t* client, char* ip, int port);
int connection(client_t* client);

//  client

int client_engine(client_t* client, char* ip, int port);

#endif  // CLIENT_H
