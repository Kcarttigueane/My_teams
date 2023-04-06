/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** timestamp.c
*/

#include "../include/lib.h"

char* timestamp_to_string(time_t timestamp)
{
    char* str = calloc(20, sizeof(char));
    strftime(str, 20, "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
    return str;
}

time_t string_to_timestamp(char* str)
{
    struct tm time = {0};
    strptime(str, "%Y-%m-%d %H:%M:%S", &time);
    return mktime(&time);
}
