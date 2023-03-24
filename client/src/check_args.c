/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** check_args
*/

#include "../include/client.h"

static bool is_help_valid(const char* help)
{
    if (regex_match("^(-{1,2}help)$", help)) {
        fprintf(stdout, CLIENT_USAGE);
        return true;
    }
    return false;
}

static bool is_ip_valid(const char* ip)
{
    if (!regex_match("^^[0-9.]+$", ip)) {
        fprintf(stdout, "error: invalid IP address");
        return false;
    }
    return true;
}

static bool is_port_valid(const char* port)
{
    if (!regex_match("^[0-9]+$", port)) {
        fprintf(stdout, "error: invalid port number");
        return false;
    }
    return true;
}

bool are_arguments_valid(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stdout, "error: invalid number of arguments");
        return false;
    }

    if (is_help_valid(argv[1]))
        return true;

    if (argc != 3) {
        fprintf(stdout, "error: invalid number of arguments");
        return false;
    }

    if (!is_ip_valid(argv[1]))
        return false;

    if (!is_port_valid(argv[2]))
        return false;

    return true;
}
