/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** generate_uuid.c
*/

#include "../include/my_teams.h"

char* generate_uuid(void)
{
    char* uuid_str = (char *)malloc(MAX_UUID_LENGTH * sizeof(char));

    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}
