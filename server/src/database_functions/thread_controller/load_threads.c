/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** load_threads.c
*/

#include "../../../include/server.h"

static void handle_curly_brace(database_t* db, thread_t** current_thread,
reply_t** current_reply)
{
    if (*current_thread) {
        reply_t* reply = (reply_t*)calloc(1, sizeof(reply_t));
        LIST_INSERT_HEAD(&(*current_thread)->replies, reply, entries);
    } else {
        *current_thread = (thread_t*)calloc(1, sizeof(thread_t));
        LIST_INSERT_HEAD(&db->threads, *current_thread, entries);
        LIST_INIT(&(*current_thread)->replies);
    }
}

static void handle_closing_brace(thread_t** current_thread,
reply_t** current_reply)
{
    if (*current_reply) {
        *current_reply = NULL;
    } else if (*current_thread) {
        *current_thread = NULL;
    }
}

static void handle_key_value_pairs(char* line, thread_t* current_thread,
reply_t* current_reply)
{
    char key[64] = {0}, value[256] = {0};
    sscanf(line, " \"%[^\"]\": \"%[^\"]\"", key, value);

    (!strcmp(key, "uuid"))
    ? (current_reply ? strcpy(current_reply->uuid, value)
    : strcpy(current_thread->uuid, value))
    : (!strcmp(key, "title")) ? strcpy(current_thread->title, value)
    : (!strcmp(key, "message")) ? strcpy(current_thread->message, value)
    : (!strcmp(key, "related_channel_uuid"))
    ? strcpy(current_thread->related_channel_uuid, value)
    : (!strcmp(key, "creator_uuid"))
    ? strcpy(current_thread->creator_uuid, value)
    : (!strcmp(key, "body")) ? strcpy(current_reply->body, value)
    : (!strcmp(key, "related_thread_uuid") && current_reply)
    ? strcpy(current_reply->related_thread_uuid, value)
    : (!strcmp(key, "created_at"))
    ? current_thread->created_at = (time_t)atoi(value)
    : (void)0;
}

void load_threads_from_file(database_t* db)
{
    FILE* file = open_file("libs/database/threads.json", "r");
    if (!file)
        return;

    char line[256] = {0};
    thread_t* current_thread = NULL;
    reply_t* current_reply = NULL;

    LIST_INIT(&db->threads);

    while (fgets(line, sizeof(line), file)) {
        (strstr(line, "{")) ?
        handle_curly_brace(db, &current_thread, &current_reply) :
        (strstr(line, "}")) ?
        handle_closing_brace(&current_thread, &current_reply) :
        (current_thread) ?
        handle_key_value_pairs(line, current_thread, current_reply) : 0;
    }

    fclose(file);
}
