/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** thread.h
*/

#pragma once

#include <sys/queue.h>
#include "message.h"
#include "channel.h"

typedef struct thread_s {
    char uuid[MAX_UUID_STR_LEN];
    char title[MAX_NAME_LENGTH];
    char message[MAX_BODY_LENGTH];
    char related_channel_uuid[MAX_UUID_STR_LEN];
    char creator_uuid[MAX_UUID_STR_LEN];
    time_t created_at;
    LIST_HEAD(replies_head, reply_s) replies;
    LIST_ENTRY(thread_s) entries;
} thread_t;

typedef struct create_thread_params_s {
    char title[MAX_NAME_LENGTH];
    char message[MAX_BODY_LENGTH];
    char related_channel_uuid[MAX_UUID_STR_LEN];
    char creator_uuid[MAX_UUID_STR_LEN];
} create_thread_params_t;

thread_t* create_thread(database_t* db, create_thread_params_t* params);
void list_threads(database_t* db);
void free_all_threads(database_t* db);
void list_replies_for_thread(database_t* db, char* thread_uuid);
thread_t* find_thread_by_uuid(database_t* database, char* uuid);
