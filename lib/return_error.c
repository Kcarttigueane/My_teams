/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** handle_error.c
*/

#include "../include/lib.h"

int handle_error(const char* msg)
{
    fprintf(stdout, "%s\n", msg);
    return 84;
}
