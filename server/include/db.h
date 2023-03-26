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

    // LIST_HEAD(messages_head, message_s) messages;
