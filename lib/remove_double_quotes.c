/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** remove_double_quotes.c
*/

#include "../include/lib.h"

void remove_quotes(char* str)
{
    size_t len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        strncpy(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}
