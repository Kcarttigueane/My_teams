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
    user_t* tmp;

    LIST_FOREACH_SAFE(user, &(db->users), entries, tmp) {
        LIST_REMOVE(user, entries);
        free(user);
    }
}
