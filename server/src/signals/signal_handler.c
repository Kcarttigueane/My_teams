/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** signal_handler.c
*/

#include "../../include/server.h"

void sigint_handler(__attribute_maybe_unused__ int sig)
{
    stop_server = true;
}

int setup_signal_handler(void)
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == FAILURE)
        handle_error("Sigaction failed");

    return SUCCESS;
}
