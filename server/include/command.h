/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** command.h
*/

#pragma once

    #define HELP_DESCRIPTION                                                \
        "?[command_name] : List all available command or specific command " \
        "details if command_name is provided\r\n"
    #define LOGIN_DESCRIPTION \
        "[\"user_name\"] : Set the user_name used by the client\r\n"
    #define LOGOUT_DESCRIPTION ": Disconnect the client from the server\r\n"
    #define USERS_DESCRIPTION \
        ": Get the list of all users that exist on the domain\r\n"
    #define USER_DESCRIPTION \
        "[\"user_uuid\"] : Get details about the requested user\r\n"
    #define SEND_DESCRIPTION                                                 \
        "[\"user_uuid\"] [\"message_body\"] : Send a message to a specific " \
        "user\r\n"
    #define MSGS_DESCRIPTION                                                \
        "[\"user_uuid\"] : List all messages exchanged with the specified " \
        "user\r\n"
    #define SUBSCRIBE_DESCRIPTION                                          \
        "[\"team_uuid\"] : Subscribe to the events of a team and its sub " \
        "directories\r\n"
    #define SUBSCRIBED_DESCRIPTION                                        \
        "?[\"team_uuid\"] : List all subscribed teams or list all users " \
        "subscribed to a team\r\n"
    #define UNSUBSCRIBE_DESCRIPTION "[\"team_uuid\"] : Unsubscribe from \
    a team\r\n"
    #define USE_DESCRIPTION                                                   \
        "?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"] : Sets the " \
        "command context to a team/channel/thread\r\n"
    #define CREATE_DESCRIPTION \
        "[\"team_name\"] : Create a new team\r\n"
    #define LIST_DESCRIPTION \
        "?[\"team_uuid\"] ?[\"channel_uuid\"] : List all teams or list all \
    channels of a team\r\n"
    #define INFO_DESCRIPTION \
        "?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"] : Display \
    details of the current resource\r\n"

    #define MAX_ARGS 4

    typedef void (*command_func_t)(void);

    typedef struct command_s {
        char* name;
        command_func_t func;
        char* description;
        bool need_login;
        int nb_args[MAX_ARGS];
    } command_t;

    // ! PROTOTYPES:

void help(void);
void login(void);
void logout(void);
void msgs(void);
void send_msg(void);
void subscribe(void);
void subscribed(void);
void unsubscribe(void);
void use(void);
void create(void);
void list(void);
void info(void);
void user(void);
void users(void);
