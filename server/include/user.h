/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user.h
*/

#pragma once

#include "db.h"

typedef struct user_s {
    char uuid[MAX_UUID_STR_LEN];
    char username[MAX_NAME_LENGTH];
    LIST_ENTRY(user_s) entries;
} user_t;

user_t *create_user(database_t* database, char* username);

char *print_users(database_t* db);

void free_users(database_t* db);

user_t* find_user_by_uuid(database_t* db, char* uuid);

user_t* find_user_by_username(database_t* db, char* username);
