/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** reply.h
*/

#pragma once

#include "user.h"

typedef struct reply_s {
    char uuid[MAX_UUID_LENGTH];
    char body[MAX_BODY_LENGTH];
    char related_thread_uuid[MAX_UUID_LENGTH];
    char creator_uuid[MAX_UUID_LENGTH];
    time_t created_at;
    LIST_ENTRY(reply_s) entries;
} reply_t;

char* list_replies_for_thread(database_t* db, char* thread_uuid);
reply_t* add_reply_to_thread(database_t* db, char* thread_uuid,
char* reply_body, char* creator_uuid);

// ! HELPERS FUNCTIONS:

void reply_creation_send_json_resp(list_args_t* args, reply_t* new_reply,
char *thread_uuid, char *team_uuid);
