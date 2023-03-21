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

    #include "user.h"
    #include "team.h"
    #include "channel.h"
    #include "comment.h"
    #include "message.h"
    #include "thread.h"
    #include "discussion.h"

#endif  // SERVER_H
