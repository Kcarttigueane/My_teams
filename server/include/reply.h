/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** reply.h
*/

#pragma once

#include "user.h"

typedef struct reply_s {
    char uuid[MAX_UUID_STR_LEN];
    char body[MAX_BODY_LENGTH];
    char related_thread_uuid[MAX_UUID_STR_LEN];
    time_t created_at;
    LIST_ENTRY(reply_s) entries;
} reply_t;

void list_replies_for_thread(database_t* db, char* thread_uuid);
