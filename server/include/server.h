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
        int socket_fd;
        char current_user_uuid[MAX_UUID_STR_LEN];
        char current_team_uuid[MAX_UUID_STR_LEN];
        char current_channel_uuid[MAX_UUID_STR_LEN];
        char current_thread_uuid[MAX_UUID_STR_LEN];
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

    typedef enum {
        CONNECTION_SUCCESSFUL = 200,
        DISCONNECTION_SUCCESSFUL = 201,
        MESSAGE_SENT = 202,
        THREAD_REPLY_CREATED = 203,
        TEAM_CREATED = 204,
        CHANNEL_CREATED = 205,
        THREAD_CREATED = 206,
        LIST_USERS = 207,
        LIST_TEAMS = 208,
        LIST_CHANNELS = 209,
        LIST_THREADS = 210,
        LIST_THREAD_REPLIES = 211,
        LIST_PRIVATE_MESSAGES = 212,
        USER_INFO = 213,
        TEAM_INFO = 214,
        CHANNEL_INFO = 215,
        THREAD_INFO = 216,
        TEAM_CREATED_NOTIFICATION = 217,
        CHANNEL_CREATED_NOTIFICATION = 218,
        THREAD_CREATED_NOTIFICATION = 219,
        REPLY_CREATED_NOTIFICATION = 220,
        SUBSCRIBED_TO_TEAM = 221,
        UNSUBSCRIBED_FROM_TEAM = 222,
        UNKNOWN_TEAM = 400,
        UNKNOWN_CHANNEL = 401,
        UNKNOWN_THREAD = 402,
        UNKNOWN_USER = 403,
        UNAUTHORIZED = 404,
        ALREADY_EXISTS = 405,
        CONNECTION_DENIED = 406,
        INTERNAL_SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
    } StatusCode;


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

bool is_quoted_arg(const char* arg);
bool check_quoted_args(char** args);
bool is_login_required(const clients_t* client, size_t cmd_index);
bool handle_input_error(char** split_command);


bool is_channel_related_to_team(team_t* team, channel_t* channel);
bool is_thread_related_to_channel_to_team(team_t* team, channel_t* channel,
thread_t* thread);

extern const command_t COMMANDS_DATA[];
extern const size_t COMMANDS_DATA_SIZE;

#endif  // SERVER_H
