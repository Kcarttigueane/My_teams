/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** signal_handler.c
*/

#include "../../include/server.h"

void sigint_handler(int sig)
{
    (void)sig;
    printf("SIGINT received, exiting server gracefully ... \n");
    exit(SUCCESS);
}

void sigterm_handler(int sig)
{
    (void)sig;
    printf("SIGTERM received, exiting server gracefully ... \n");
    exit(SUCCESS);
}
