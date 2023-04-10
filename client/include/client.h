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

    // ! My includes:

    #include "../../include/lib.h"
    #include "../../include/my_teams.h"
    #include "../../libs/myteams/logging_client.h"

    // ! STRUCTURES:

    typedef struct client_data {
        int socket_fd;
        fd_set read_fds;
    } client_data_t;

    typedef void (*func_t)(char* json_response);

    typedef struct events_s {
        int status_code;
        func_t function;
    } events_t;


// ! PROTOTYPES:

char** parse_inputs(char* command);
void free_tokens(char** tokens);

bool are_arguments_valid(int argc, char* argv[]);

int connect_to_server(const char* server_address, int port);
int client_loop(client_data_t* client);

int get_status_code(const char* json_string);

// ! SIGNALS:

void sigint_handler(int sig);
int setup_signal_handler(void);

// ! CLIENT LOOP FUNCTIONS:

int handle_server_input(client_data_t* client, char* buffer);
int handle_user_input(client_data_t* client);

// ! PARSE JSON SERVER RESPONSE:

bool extract_value(const char* key, char* json_str, char* value,
int max_length);
bool extract_boolean_value(const char* key, char* json_str, bool* value);

// ! EVENTS:

void user_already_exist(char *json_response);
void channel_created(char *json_response);
void channel_created_notification(char *json_response);
void connection_successful(char *json_response);
void disconnection_successful(char *json_response);
void info_channel(char *json_response);
void info_team(char *json_response);
void info_thread(char *json_response);
void info_user(char *json_response);
void internal_server_error(char *json_response);
void message_received(char *json_response);
void not_implemented(char *json_response);
void print_channels(char *json_response);
void print_messages(char *json_response);
void print_teams(char *json_response);
void print_thread_replies(char *json_response);
void print_threads(char *json_response);
void print_users(char *json_response);
void reply_created_notification(char *json_response);
void subscribed_to_team(char *json_response);
void team_created(char *json_response);
void team_created_notification(char *json_response);
void thread_created(char *json_response);
void thread_created_notification(char *json_response);
void thread_reply_created(char *json_response);
void unauthorized(char *json_response);
void unknow_channel(char *json_response);
void unknow_team(char *json_response);
void unknow_thread(char *json_response);
void unknow_user(char *json_response);
void unsubscribed_from_team(char *json_response);


extern const char* ENDPOINTS_LIST[];
extern const size_t ENDPOINTS_LIST_SIZE;

extern const events_t LIST_EVENTS_CODE[];
extern const size_t LIST_EVENTS_CODE_SIZE;

extern volatile sig_atomic_t stop_server;

#endif  // CLIENT_H
