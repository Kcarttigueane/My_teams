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
    user_t* creator;
    team_t* team;
    char users[10][MAX_UUID_STR_LEN];
    size_t nb_users;
    int users_count;
    LIST_ENTRY(channel_s) entries;
} channel_t;

void list_channels(database_t* db);
void free_channels(database_t* db);
channel_t* create_channel(database_t* db, char* name, char* description,
user_t* creator, team_t* team);
bool is_channel_exist(database_t* db, char* team_uuid);
void display_channel_info(database_t* db, char* channel_uuid);
