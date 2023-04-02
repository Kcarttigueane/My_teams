/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** channel.h
*/

#pragma once

#include "db.h"

typedef struct channel_s {
    char uuid[MAX_UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_UUID_LENGTH];
    char creator_uuid[MAX_UUID_LENGTH];
    char users[10][MAX_UUID_LENGTH];
    size_t nb_users;
    time_t created_at;
    LIST_ENTRY(channel_s) entries;
} channel_t;

typedef struct create_channel_params_s {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_UUID_LENGTH];
    char creator_uuid[MAX_UUID_LENGTH];
} create_channel_params_t;

// ! CREATE

create_channel_params_t init_create_channel_params(list_args_t* args);
channel_t* create_channel(database_t* db, create_channel_params_t* param);

// ! FIND

channel_t* find_channel_by_uuid(database_t* db, char* channel_uuid);
bool is_channel_already_exist(database_t* db, char* channel_name);

// ! ADD / REMOVE / UPDATE

bool add_user_to_channel(database_t* db, char* channel_uuid, char* user_uuid);
bool remove_user_from_channel(database_t* db, char* channel_uuid,
    char* user_uuid);

bool remove_user_from_team_channels(database_t* db, char* team_uuid,
char* user_uuid);
bool add_user_to_team_channels(database_t* db, char* team_uuid,
char* user_uuid);

// ! LIST

char* list_channels(database_t* db, char* team_uuid);

// ! FREE

void free_channels(database_t* db);

// ! DEBUG

void debug_channel(channel_t* new_channel);

// ! HELPERS FUNCTIONS:

void team_channel_send_json_resp(list_args_t* args, channel_t* new_channel);
