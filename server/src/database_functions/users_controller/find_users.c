/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** find_users.c
*/

#include "../../../include/server.h"

user_t* find_user_by_uuid(database_t* db, char* uuid)
{
    user_t* user;

    LIST_FOREACH(user, &db->users, entries) {
        if (!strcmp(user->uuid, uuid))
            return user;
    }
    printf("Error: User not found\n");
    return NULL;
}

user_t* find_user_by_username(database_t* db, char* username)
{
    user_t* user;

    LIST_FOREACH(user, &db->users, entries) {
        if (!strcmp(user->username, username))
            return user;
    }
    printf("Error: User not found\n");
    return NULL;
}
