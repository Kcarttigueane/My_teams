/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** db.h
*/

#pragma once

#include <sys/queue.h>
#include "server.h"

typedef struct database {
    LIST_HEAD(teams_head, team_s) teams;
    LIST_HEAD(channels_head, channel_s) channels;
    LIST_HEAD(threads_head, thread_s) threads;
    LIST_HEAD(discussions_head, discussion_s) discussions;
    LIST_HEAD(users_head, user_s) users;
} database_t;

database_t init_database(void);
void free_database(database_t* database);

// ! SAVE AND LOAD [USERS]

void save_users_to_file(database_t* db);
void load_users_from_file(database_t* db);

// ! SAVE AND LOAD [DISCUSSIONS]

void save_discussions_to_file(database_t* db);
void load_discussions_from_file(database_t* db);

// ! SAVE AND LOAD [TEAMS]

void save_teams_to_file(database_t* db);
void load_teams_from_file(database_t* db);

// ! SAVE AND LOAD [CHANNELS]

void save_channels_to_file(database_t* db);
void load_channels_from_file(database_t* db);

// ! SAVE AND LOAD [THREADS]

void save_threads_to_file(database_t* db);
void load_threads_from_file(database_t* db);

// ! UTILS:

bool is_channel_related_to_team(team_t* team, channel_t* channel);
bool is_thread_related_to_channel_to_team(team_t* team, channel_t* channel,
thread_t* thread);
