/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_user.c
*/

#include "../../../include/server.h"
#include "../../../../include/color.h"

static user_t* create_user_object(char* username)
{
    user_t* new_user = (user_t*)calloc(1, sizeof(user_t));

    if (new_user == NULL) {
        printf("Error: Failed to allocate memory for new user\n");
        return false;
    }

    char* uuid_str = generate_uuid();

    strncpy(new_user->uuid, uuid_str, MAX_UUID_STR_LEN);
    strncpy(new_user->username, username, MAX_NAME_LENGTH);

    free(uuid_str);

    return new_user;
}

user_t* create_user(database_t* database, char* username)
{
    user_t* user;

    LIST_FOREACH(user, &database->users, entries) {
        if (!strcmp(user->username, username)) {
            printf("Error: Username already exists\n");
            return NULL;
        }
    }
    user_t* new_user = create_user_object(username);

    if (!new_user)
        return NULL;

    LIST_INSERT_HEAD(&database->users, new_user, entries);

    debug_user(new_user);
    return new_user;
}
