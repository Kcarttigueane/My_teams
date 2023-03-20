/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

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

    // ! My includes:

    #include "my_teams.h"
    #include "lib.h"


    #define CLIENT_USAGE \
        "USAGE: ./myteams_cli ip port\n\
        \tip is the server ip address on which the server socket listens\n\
        \tport is the port number on which the server socket listens\n"

#endif  // CLIENT_H
