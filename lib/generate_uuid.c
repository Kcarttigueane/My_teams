/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** generate_uuid.c
*/

#include <uuid/uuid.h>
#include <stdlib.h>

#define MAX_UUID_STR_LEN 37

char* generate_uuid(void)
{
    char* uuid_str = (char *)malloc(MAX_UUID_STR_LEN * sizeof(char));

    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}
