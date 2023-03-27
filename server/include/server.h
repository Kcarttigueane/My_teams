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


    // ! STRUCTURES:

    typedef struct server_data {
        int PORT;
        int socket_fd;
        fd_set readfds;
    } server_data_t;

    typedef struct clients {
        int client_socket_fd;
        char current_user_uuid[MAX_UUID_STR_LEN];
        char current_team_uuid[MAX_UUID_STR_LEN];
        char current_channel_uuid[MAX_UUID_STR_LEN];
        char cur_thread_uui[MAX_UUID_STR_LEN];
        bool is_logged;
        int use_args_count;
    } clients_t;

    #include "db.h"

    typedef struct list_args {
        server_data_t* server_data;
        char** split_command;
        clients_t* client;
        database_t* db;
    } list_args_t;

    enum status_codes {
        CONNECTION_SUCCESSFUL = 200,
        DISCONNECTED_SUCCESSFUL = 201,
        HELP_LISTED = 202,
        USERS_LISTED = 203,
        USER_INFORMATION = 204,
        MESSAGE_SENT = 205,
        MESSAGE_LISTED = 206,
        SUBSCRIBED = 207,
        UNSUBSCRIBED = 208,
        CONTEXT_SPECIFIED = 209,
        RESOURCE_CREATED = 210,
        CONNECTION_DENIED = 400,
    };

    #include "user.h"
    #include "team.h"
    #include "channel.h"
    #include "thread.h"
    #include "message.h"
    #include "discussion.h"
    #include "signals.h"
    #include "command.h"
    #include "reply.h"

    // ! PROTOTYPES:

bool are_arguments_valid(int argc, char const* argv[]);

int bind_and_listen_socket(server_data_t* s);
int initialize_server(server_data_t* s);
void server_loop(server_data_t* s, database_t* db);

void accept_new_connection(int server_socket, clients_t *clients);
void handle_client_activity(clients_t *clients, server_data_t* s,
database_t* db);
void parse_client_input(clients_t* clients, server_data_t* s,
char* input_buffer, database_t* db);

extern const command_t COMMANDS_DATA[];
extern const size_t COMMANDS_DATA_SIZE;

#endif  // SERVER_H
