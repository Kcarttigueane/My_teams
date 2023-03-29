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

// ! CREATE

thread_t* create_thread(database_t* db, create_thread_params_t* params);

// ! FIND

thread_t* find_thread_by_uuid(database_t* database, char* uuid);

// ! LIST

char* list_threads(database_t* db, char *channel_uuid);

// ! LOAD

void load_threads_from_file(database_t* db);

// ! FREE

void free_all_threads(database_t* db);

// ! DEBUG

void debug_thread(thread_t* new_thread);
