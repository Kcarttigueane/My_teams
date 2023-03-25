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

    enum ErrorCodes {
        SUCCESS = 0,
        FAILURE = -1,
        ERROR = 84
    };

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define MAX_UUID_STR_LEN 37

    #define exit_with_error(msg) \
        do {                  \
            fprintf(stdout, msg); \
            exit(ERROR);      \
        } while (0);
