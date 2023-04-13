/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** team.h
*/

#pragma once

#include "db.h"

typedef struct team_s {
    char uuid[MAX_UUID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char users[10][MAX_UUID_LENGTH];
    int users_count;
    time_t created_at;
    LIST_ENTRY(team_s) entries;
} team_t;

// ! CREATE

team_t* create_team(database_t* db, char* name, char* description);

// ! FIND

team_t* find_team_by_uuid(database_t* db, char* team_uuid);
bool is_team_already_exist(database_t* db, char* team_name);

// ! LIST

char* list_teams(database_t* db);
char* list_subscribed_teams(database_t* db, char* user_uuid);
char* list_users_subscribed_to_team(database_t* db, team_t *team);
// ! FREE

void free_teams(database_t* db);

// ! ADD / REMOVE [user]

bool add_user_to_team(database_t* db, char* team_uuid, char* user_uuid);
bool remove_user_from_team(database_t* db, char* team_uuid, char* user_uuid);

// ! DEBUG

void debug_team(team_t* new_team);

// ! HELPERS FUNCTIONS:

void team_creation_send_json_resp(list_args_t* args, team_t* new_team);

// ! IS TEAM EMPTY

bool is_team_list_empty(database_t* db);

// ! IS USER PAR OF THE TEAM

bool is_user_in_team(team_t* new_team, char* user_uuid);
