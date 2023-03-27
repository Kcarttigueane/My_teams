/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** channel.h
*/

#pragma once

#include "db.h"

typedef struct channel_s {
    char uuid[MAX_UUID_STR_LEN];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_UUID_STR_LEN];
    char creator_uuid[MAX_UUID_STR_LEN];
    char users[10][MAX_UUID_STR_LEN];
    size_t nb_users;
    int users_count;
    time_t created_at;
    LIST_ENTRY(channel_s) entries;
} channel_t;

typedef struct create_channel_params_s {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_UUID_STR_LEN];
    char creator_uuid[MAX_UUID_STR_LEN];
} create_channel_params_t;

channel_t* create_channel(database_t* db, create_channel_params_t* param);

void list_channels(database_t* db);
void free_channels(database_t* db);

bool is_channel_exist(database_t* db, char* team_uuid);
void display_channel_info(database_t* db, char* channel_uuid);

bool add_user_to_channel(database_t* db, char* channel_uuid, char* user_uuid);
bool remove_user_from_channel(database_t* db, char* channel_uuid,
char* user_uuid);
