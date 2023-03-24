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
    channel_t* channel;
    user_t* creator;
    LIST_HEAD(replies_head, reply_s) replies;
    LIST_ENTRY(thread_s) entries;
} thread_t;

thread_t* create_thread(database_t* db, char* title, char* message,
channel_t* channel, user_t* creator);
thread_t* find_thread_by_uuid(database_t* database, char* uuid);
bool add_reply_to_thread(database_t* db, char* thread_uuid, char* reply_body,
user_t* user);
bool is_thread_exist(database_t* db, char* thread_uuid);
void list_replies_for_thread(database_t* db, char* thread_uuid);
void list_threads(database_t* db);
