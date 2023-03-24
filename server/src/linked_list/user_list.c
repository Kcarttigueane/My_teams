/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user_list.c
*/

#include "../../include/server.h"

bool create_user(database_t* database, char* uuid, char* username)
{
    user_t* user;

    LIST_FOREACH(user, &database->users, entries) {
        if (strcmp(user->username, username) == 0) {
            printf("Error: Username already exists\n");
            return false;
        }
    }
    user_t* new_user = malloc(sizeof(user_t));
    if (new_user == NULL) {
        printf("Error: Failed to allocate memory for new user\n");
        return false;
    }
    strncpy(new_user->uuid, uuid, MAX_UUID_STR_LEN);
    strncpy(new_user->username, username, MAX_NAME_LENGTH);
    LIST_INSERT_HEAD(&database->users, new_user, entries);
    printf("User created with UUID %s and username %s\n", uuid, username);

    return true;
}

void print_users(database_t* db)
{
    user_t* user;

    if (LIST_EMPTY(&db->users)) {
        printf("User list is empty.\n");
        return;
    }

    printf("User list:\n");

    LIST_FOREACH(user, &db->users, entries) {
        printf("UUID: %s, username: %s\n", user->uuid, user->username);
    }
}

void free_users(database_t* db)
{
    user_t* user;

    while (!LIST_EMPTY(&db->users)) {
        user = LIST_FIRST(&db->users);
        LIST_REMOVE(user, entries);
        free(user);
    }
}

user_t* find_user_by_uuid(database_t* db, char* uuid)
{
    user_t* user;

    LIST_FOREACH(user, &db->users, entries) {
        if (!strcmp(user->uuid, uuid))
            return user;
    }
    return NULL;
}
