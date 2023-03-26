/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** db.h
*/

#pragma once

#include "server.h"
#include <sys/queue.h>
typedef struct database {
    LIST_HEAD(teams_head, team_s) teams;
    LIST_HEAD(channels_head, channel_s) channels;
    LIST_HEAD(threads_head, thread_s) threads;
    LIST_HEAD(discussions_head, discussion_s) discussions;
    LIST_HEAD(users_head, user_s) users;
} database_t;

database_t init_database(void);

// ! SAVE AND LOAD [USERS]

void save_users_to_file(database_t* db);
void load_users_from_file(database_t* db);

// ! SAVE AND LOAD [DISCUSSIONS]

void save_discussions_to_file(database_t* db);
void load_discussions_from_file(database_t* db);
