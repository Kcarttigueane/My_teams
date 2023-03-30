/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** is_start_end_json.c
*/

#include "../include/lib.h"

bool is_start_json(char* line)
{
    return strstr(line, "{") != NULL;
}

bool is_end_json(char* line)
{
    return strstr(line, "}") != NULL;
}
