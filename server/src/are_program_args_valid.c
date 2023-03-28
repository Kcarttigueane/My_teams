/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** are_program_args_valid.c
*/

#include "../include/server.h"

bool are_arguments_valid(int argc, char const* argv[])
{
    if (argc != 2 || regex_match("[-]{1,2}h(elp)?", argv[1]) ||
        !regex_match("^[0-9]+$", argv[1])) {
        fprintf(stdout, SERVER_USAGE);
        return false;
    }
    return true;
}
