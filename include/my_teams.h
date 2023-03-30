/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** my_teams.h
*/

#pragma once

    #include <sys/select.h>
    #include <sys/socket.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/un.h>

    #include <netinet/in.h>

    #include <arpa/inet.h>
    #include <netdb.h>

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "unistd.h"

    #include <errno.h>

    #include <signal.h>
    #include <stdbool.h>

    #include <dirent.h>

    #include <libgen.h>
    #include <limits.h>

    #include <uuid/uuid.h>
    #include <signal.h>
    #include <sys/queue.h>

    #include <time.h>

    enum ErrorCodes {
        SUCCESS = 0,
        FAILURE = -1,
        ERROR = 84
    };

    enum {
        MAX_NAME_LENGTH = 32,
        MAX_DESCRIPTION_LENGTH = 255,
        MAX_BODY_LENGTH = 512,
        MAX_UUID_STR_LEN = 37,
        MAX_CLIENTS = 10,
        BUFFER_SIZE = 1024,
        KEY_BUFFER = 64
    };

    typedef enum {
        CONNECTION_SUCCESSFUL = 200,
        DISCONNECTION_SUCCESSFUL = 201,
        MESSAGE_SENT = 202,

        // *---------------------------------------* //

        THREAD_REPLY_CREATED = 203,
        TEAM_CREATED = 204,
        CHANNEL_CREATED = 205,
        THREAD_CREATED = 206,

        // *---------------------------------------* //

        PRINT_USERS = 207,
        PRINT_TEAMS = 208,
        PRINT_CHANNELS = 209,
        PRINT_THREADS = 210,
        PRINT_THREAD_REPLIES = 211,
        PRINT_PRIVATE_MESSAGES = 212,

        // *---------------------------------------* //

        UNKNOWN_TEAM = 400,
        UNKNOWN_CHANNEL = 401,
        UNKNOWN_THREAD = 402,
        UNKNOWN_USER = 403,

        // *---------------------------------------* //

        UNAUTHORIZED = 404,
        ALREADY_EXISTS = 405,

        // *---------------------------------------* //

        INFO_USER = 213,
        INFO_TEAM = 214,
        INFO_CHANNEL = 215,
        INFO_THREAD = 216,

        // *---------------------------------------* //

        TEAM_CREATED_NOTIFICATION = 217,
        CHANNEL_CREATED_NOTIFICATION = 218,
        THREAD_CREATED_NOTIFICATION = 219,
        REPLY_CREATED_NOTIFICATION = 220,

        // *---------------------------------------* //

        SUBSCRIBED_TO_TEAM = 221,
        UNSUBSCRIBED_FROM_TEAM = 222,

        // *----------- ADDITIONAL CODE -----------* //

        CONNECTION_DENIED = 406,
        INTERNAL_SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
    } StatusCode;


    #ifndef LIST_FOREACH_SAFE
        #define LIST_FOREACH_SAFE(var, head, field, tvar) \
            for ((var) = LIST_FIRST((head));              \
                (var) && ((tvar) = LIST_NEXT((var), field), 1); (var) = (tvar))
    #endif


    #define exit_with_error(msg)  \
        do {                      \
            fprintf(stdout, msg); \
            exit(ERROR);          \
        } while (0);

        #define CLIENT_PROMPT "➜ "

