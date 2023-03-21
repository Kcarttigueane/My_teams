/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "include/server.h"

int main(int argc, char const* argv[])
{
    if (argc != 2 || regex_match("[-]{1,2}h(elp)?", argv[1])) {
        printf(SERVER_USAGE);
        return ERROR;
    }

    uuid_t uuid;
    uuid_generate_random(uuid);

    char uuid_str[MAX_UUID_STR_LEN];
    uuid_unparse(uuid, uuid_str);

    printf("Generated UUID: %s\n", uuid_str);

    return 0;
}
