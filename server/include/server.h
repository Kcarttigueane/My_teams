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

    #include "command.h"
    #include "user.h"
    #include "team.h"
    #include "channel.h"
    #include "comment.h"
    #include "message.h"
    #include "thread.h"
    #include "discussion.h"
    #include "signals.h"

    // ! STRUCTURES:

    typedef struct server_data {
        int PORT;
        int server_socket_fd;
        int fd_max, fd_num, read_input_len;
        struct sockaddr_in server_address, data_address;
        struct timeval timeout;
        fd_set fds, copy_fds;
        size_t nb_clients;
    } server_data_t;

#endif  // SERVER_H
