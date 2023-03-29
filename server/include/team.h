/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** team.h
*/

#pragma once

#include "db.h"

typedef struct team_s {
    char uuid[MAX_UUID_STR_LEN];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char users[10][MAX_UUID_STR_LEN];
    int users_count;
    time_t created_at;
    LIST_ENTRY(team_s) entries;
} team_t;

team_t* create_team(database_t* db, char* name, char* description);
char* list_teams(database_t* db);
void free_teams(database_t* db);
bool is_team_exists(database_t* db, char* team_uuid);
bool add_user_to_team(database_t* db, char* team_uuid, char* user_uuid);
bool remove_user_from_team(database_t* db, char* team_uuid, char* user_uuid);
team_t* find_team_by_uuid(database_t* db, char* team_uuid);

void debug_team(team_t* new_team);
