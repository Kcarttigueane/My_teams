/*
** EPITECH PROJECT, 2023
** MyTeams
** File description:
** main.c
*/

#ifndef SERVER_H
    #define SERVER_H

    // ! Macros:

    #define SERVER_USAGE \
        "USAGE: ./myteams_server port\n\n\
        \tport is the port number on which the server socket listens.\n"

    #define MAX_CLIENTS 10
    #define BUFFER_SIZE 1024

    // ! My includes:

    #include "../../include/my_teams.h"
    #include "../../include/lib.h"

    #include "command.h"
    #include "user.h"
    #include "team.h"
    #include "channel.h"
    #include "comment.h"
    #include "message.h"
    #include "thread.h"
    #include "discussion.h"
    #include "signals.h"

    // ! STRUCTURES:

    typedef struct server_data {
        int PORT;
        int socket_fd;
        fd_set readfds;
    } server_data_t;

    typedef struct clients {
        int client_socket_fd;
        char *username;
        bool is_logged;
    } clients_t;

    // ! PROTOTYPES:

bool are_arguments_valid(int argc, char const* argv[]);

int bind_and_listen_socket(server_data_t* s);
int initialize_server(server_data_t* s);
void server_loop(server_data_t *s);

void accept_new_connection(int server_socket, clients_t clients[MAX_CLIENTS]);
int get_max_socket_descriptor(clients_t clients[MAX_CLIENTS],
int server_socket);
void handle_client_activity(clients_t clients[MAX_CLIENTS], server_data_t* s);

#endif  // SERVER_H
