/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** generate_uuid.c
*/

#include "../include/lib.h"

char* generate_uuid()
{
    char* uuid_str = malloc(MAX_UUID_STR_LEN * sizeof(char));

    uuid_t uuid;
    uuid_generate(uuid);
    // Convert UUID to string
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}
