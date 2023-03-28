/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user_list.c
*/

#include "../../../include/server.h"

void free_users(database_t* db)
{
    user_t* user;

    while (!LIST_EMPTY(&db->users)) {
        user = LIST_FIRST(&db->users);
        LIST_REMOVE(user, entries);
        free(user);
    }
}
