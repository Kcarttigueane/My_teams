/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "include/client.h"

char *command_list[] = {
    "/help",
    "/login",
    "/logout",
    "/users",
    "/user",
    "/send",
    "/messages",
    "/subscribe",
    "/subscribed",
    "/unsubscribe",
    "/use",
    "/create",
    "/list",
    "/info",
    NULL
};

int main(int argc, char* argv[])
{
    client_t client;

    // if (argc != 2 || regex_match("[-]{1,2}h(elp)?", argv[1])) {
    //     printf(CLIENT_USAGE);
    //     return ERROR;
    // }

    client_engine(&client, argv[1], atoi(argv[2]));
    return 0;
}
