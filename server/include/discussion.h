/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** discussion.h
*/

#pragma once

#include <sys/queue.h>
#include "message.h"
#include "db.h"

typedef struct discussion_s {
    char uuid[MAX_UUID_STR_LEN];
    char sender_uuid[MAX_UUID_STR_LEN];
    char receiver_uuid[MAX_UUID_STR_LEN];
    LIST_HEAD(messages_s, message_s) messages;
    LIST_ENTRY(discussion_s) entries;
} discussion_t;

discussion_t* find_discussion_by_users(database_t* database, char* sender_uuid,
char* receiver_uuid);
discussion_t* find_discussion_by_uuid(database_t* database, char* uuid);
discussion_t* create_discussion(database_t* db, char* sender_uuid,
char* receiver_uuid);
bool add_message_to_discussion(database_t* db, char* sender_uuid,
char* receiver_uuid, char* message_body);
void free_discussions(database_t* db);
void free_discussion(discussion_t* discussion);
void print_discussion_details(database_t* db, char* discussion_uuid);
void print_all_messages_in_discussion(database_t* db, char* discussion_uuid);
