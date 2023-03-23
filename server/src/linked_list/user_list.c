/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user_list.c
*/

#include "../../include/server.h"

LIST_HEAD(user_list, user_s) users_head;

bool add_user(struct user_list* users, char* uuid, char* username)
{
    // Check if the username already exists in the list
    user_t* user;
    LIST_FOREACH(user, users, entries)
    {
        if (strcmp(user->username, username) == 0) {
            printf("Error: Username already exists\n");
            return false;
        }
    }

    // Create a new user node
    user_t* new_user = malloc(sizeof(user_t));

    if (new_user == NULL) {
        printf("Error: Failed to allocate memory for new user\n");
        return false;
    }
    strncpy(new_user->uuid, uuid, MAX_UUID_STR_LEN);
    strncpy(new_user->username, username, MAX_NAME_LENGTH);

    // Add the new user node to the linked list
    LIST_INSERT_HEAD(users, new_user, entries);

    return true;
}

void print_users()
{
    if (LIST_EMPTY(&users_head)) {
        printf("No users in list\n");
        return;
    }

    user_t* user_ptr;
    printf("Users in list:\n");

    LIST_FOREACH(user_ptr, &users_head, entries)
    {
        printf("%s %s\n", user_ptr->uuid, user_ptr->username);
    }
}

void delete_user(char* uuid)
{
    user_t* user_ptr;

    LIST_FOREACH(user_ptr, &users_head, entries)
    {
        if (strcmp(user_ptr->uuid, uuid) == 0) {
            LIST_REMOVE(user_ptr, entries);
            free(user_ptr);
            printf("User with UUID %s deleted\n", uuid);
            return;
        }
    }
    printf("User with UUID %s not found\n", uuid);
}

bool check_user_already_exist(char* username)
{
    user_t* user_ptr;

    LIST_FOREACH(user_ptr, &users_head, entries)
    {
        if (strcmp(user_ptr->username, username) == 0)
            return true;
    }
    return false;
}

user_t* get_user_by_uuid(char* uuid)
{
    user_t* user_ptr;

    LIST_FOREACH(user_ptr, &users_head, entries)
    {
        if (strcmp(user_ptr->uuid, uuid) == 0)
            return user_ptr;
    }
    printf("User with UUID %s not found\n", uuid);
    return NULL;
}
