/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

    // ! Macros:

    #define CLIENT_USAGE                 \
        "USAGE: ./myteams_cli ip port\n\
            \tip is the server ip address on which the server socket listens\n\
            \tport is the port number on which the server socket listens\n"

    #define BUFFER_SIZE 1024

    // ! My includes:

    #include "../../include/my_teams.h"
    #include "../../include/lib.h"

    // ! STRUCTURES:

    extern const char *command_list[];

    typedef struct client_data {
        char *ip;
        int port;
        int socket_fd;
        int activity;
        fd_set read_fds;
        struct sockaddr_in serv_addr;
    } client_data_t;

    // ! PROTOTYPES:

bool are_arguments_valid(int argc, char* argv[]);

int init_client(client_data_t *client);

int client_loop(client_data_t* client);

#endif  // CLIENT_H
