/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "include/server.h"

bool are_arguments_valid(int argc, char const* argv[])
{
    if (argc != 2 || regex_match("[-]{1,2}h(elp)?", argv[1]) ||
        !regex_match("^[0-9]+$", argv[1])) {
        fprintf(stdout, SERVER_USAGE);
        return false;
    }
    return true;
}

int main(int argc, char const* argv[])
{
    if (!are_arguments_valid(argc, argv))
        return ERROR;

    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);

    server_data_t server_data = {
        .PORT = atoi(argv[1]),
        .socket_fd = 0,
        .readfds = {{0}},
    };

    if (initialize_server(&server_data) == ERROR)
        return handle_error("Server initialization failed");

    server_loop(&server_data);

    return SUCCESS;
};
