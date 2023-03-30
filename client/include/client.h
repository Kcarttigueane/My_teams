/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

    // ! Macros:

    #define CLIENT_USAGE \
        "USAGE: ./myteams_cli ip port\n\
            \tip is the server ip address on which the server socket listens\n\
            \tport is the port number on which the server socket listens\n"

    #define DEFAULT_TIMEOUT 5

    #define MAX_COMMAND_LENGTH 1000
    #define MAX_ARGUMENTS 10
    #define MAX_ARGUMENT_LENGTH 100

    // ! My includes:

    #include "../../include/lib.h"
    #include "../../include/my_teams.h"

    // ! STRUCTURES:

    extern const char* ENDPOINTS_LIST[];
    extern const size_t ENDPOINTS_LIST_SIZE;

    typedef struct client_data {
        int socket_fd;
        fd_set read_fds;
    } client_data_t;

    typedef void (*func_t)(void);

    typedef struct cmd_s {
        int status_code;
        func_t function;
    } cmd_t;


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

// ! PARSE JSON SERVER RESPONSE:

void parse_json_value(const char* json, const char* key, char* value,
size_t value_size);

// ! EVENTS:

void user_already_exist(void);
void channel_created(void);
void channel_created_notification(void);
void connection_successful(void);
void disconnection_successful(void);
void info_channel(void);
void info_team(void);
void info_thread(void);
void info_user(void);
void internal_server_error(void);
void message_sent(void);
void not_implemented(void);
void print_channels(void);
void print_messages(void);
void print_teams(void);
void print_thread_replies(void);
void print_threads(void);
void print_users(void);
void reply_created_notification(void);
void subscribed_to_team(void);
void team_created(void);
void team_created_notification(void);
void thread_created(void);
void thread_created_notification(void);
void thread_reply_created(void);
void unauthorized(void);
void unknow_channel(void);
void unknow_team(void);
void unknow_thread(void);
void unknow_user(void);
void unsubscribed_from_team(void);

#endif  // CLIENT_H
