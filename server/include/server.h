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

    // ! My includes:

    #include "../../include/my_teams.h"
    #include "../../include/lib.h"
    #include "../../libs/myteams/logging_server.h"

    // ! STRUCTURES:

    typedef struct server_data {
        int PORT;
        int socket_fd;
        fd_set readfds;
    } server_data_t;

    typedef struct clients {
        int socket_fd;
        char current_user_uuid[MAX_UUID_LENGTH];
        char current_team_uuid[MAX_UUID_LENGTH];
        char current_channel_uuid[MAX_UUID_LENGTH];
        char current_thread_uuid[MAX_UUID_LENGTH];
        bool is_logged;
        int use_args_count;
    } clients_t;

    #include "db.h"

    typedef struct list_args {
        server_data_t* server_data;
        char** split_command;
        clients_t* client;
        database_t* db;
        clients_t* clients;
    } list_args_t;

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

// ! PROGRAM PARAMETERS CHECKING:

bool are_arguments_valid(int argc, char const* argv[]);

// ! SERVER:

int bind_and_listen_socket(server_data_t* s);
int initialize_server(server_data_t* s);
int server_loop(server_data_t* s, database_t* db);
void accept_new_connection(int server_socket, clients_t *clients);
void handle_client_activity(clients_t *clients, server_data_t* s,
database_t* db);

// ! CLIENTS:

void initialize_clients(clients_t* clients);
void free_clients(clients_t* clients);

void parse_client_input(list_args_t* args, char* input_buffer);

bool is_login_required(const clients_t* client, size_t cmd_index);
bool handle_input_error(char** split_command);


bool is_channel_related_to_team(team_t* team, channel_t* channel);
bool is_thread_related_to_channel_to_team(team_t* team, channel_t* channel,
thread_t* thread);

bool validate_team_channel_thread(list_args_t* args, team_t** team,
channel_t** channel, thread_t** thread);

bool validate_team_channel(list_args_t* args, team_t** team,
channel_t** channel);

bool error_handling_name_and_description(int control_socket, char *name,
char *description);
bool error_handling_create_args(int socket_fd, int nb_args);

clients_t* find_client_by_uuid(clients_t* clients, char* uuid);

bool create_channel_error_handling(list_args_t* args, team_t* team);

extern const command_t COMMANDS_DATA[];
extern const size_t COMMANDS_DATA_SIZE;

extern volatile sig_atomic_t stop_server;

#endif  // SERVER_H
