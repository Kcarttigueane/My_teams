/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "client.h"

int main(int argc, char const* argv[])
{
    if (argc != 2 || regex_match("[-]{1,2}h(elp)?", argv[1])) {
        printf(CLIENT_USAGE);
        return ERROR;
    }
    printf("Hello, World!\n");
    return 0;
}
