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

    #define DEFAULT_TIMEOUT 5

    #define MAX_COMMAND_LENGTH 1000
    #define MAX_ARGUMENTS 10
    #define MAX_ARGUMENT_LENGTH 100

    // ! My includes:

    #include "../../include/my_teams.h"
    #include "../../include/lib.h"

    // ! STRUCTURES:

    extern const char *ENDPOINTS_LIST[];
    extern const size_t ENDPOINTS_LIST_SIZE;

    typedef struct client_data {
        int socket_fd;
        fd_set read_fds;
    } client_data_t;

    // ! PROTOTYPES:

bool are_arguments_valid(int argc, char* argv[]);

int connect_to_server(const char* server_address, int port);
int client_loop(client_data_t* client);

// ! SIGNALS:

void sigint_handler(int sig);
void sigterm_handler(int sig);

// ! CLIENT LOOP FUNCTIONS:

int handle_server_input(client_data_t* client, char* buffer);
int handle_user_input(client_data_t* client);


#endif  // CLIENT_H
