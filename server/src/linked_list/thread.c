/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** thread.c
*/

#include "../../include/server.h"

thread_t* find_thread_by_uuid(database_t* database, char* uuid)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(database->threads), entries) {
        if (!strcmp(thread->uuid, uuid))
            return thread;
    }

    return NULL;
}

thread_t* create_thread(database_t* db, create_thread_params_t* params)
{
    thread_t* new_thread = (thread_t*)malloc(sizeof(thread_t));

    if (new_thread == NULL) {
        printf("Error: Failed to allocate memory for new thread\n");
        return NULL;
    }

    char *thread_uuid = generate_uuid();
    strncpy(new_thread->uuid, thread_uuid, MAX_UUID_STR_LEN);
    strncpy(new_thread->title, params->title, MAX_NAME_LENGTH);
    strncpy(new_thread->message, params->message, MAX_BODY_LENGTH);
    strncpy(new_thread->related_channel_uuid, params->related_channel_uuid,
    MAX_UUID_STR_LEN);
    strncpy(new_thread->creator_uuid, params->creator_uuid, MAX_UUID_STR_LEN);
    new_thread->created_at = time(NULL);
    free(thread_uuid);

    LIST_INIT(&(new_thread->replies));

    LIST_INSERT_HEAD(&(db->threads), new_thread, entries);

    return new_thread;
}

reply_t *add_reply_to_thread(database_t* db, char* thread_uuid, char* reply_body,
char* user_uuid)
{
    thread_t* thread = find_thread_by_uuid(db, thread_uuid);

    if (thread == NULL) {
        printf("Error: Thread not found\n");
        return NULL;
    }

    reply_t* new_reply = malloc(sizeof(reply_t));

    if (new_reply == NULL) {
        printf("Error: Failed to allocate memory for new reply\n");
        return NULL;
    }

    char *reply_uuid = generate_uuid();
    strncpy(new_reply->uuid, reply_uuid, MAX_UUID_STR_LEN);
    strncpy(new_reply->body, reply_body, MAX_BODY_LENGTH);
    strncpy(new_reply->related_thread_uuid, thread_uuid, MAX_UUID_STR_LEN);
    new_reply->created_at = time(NULL);
    free(reply_uuid);

    LIST_INSERT_HEAD(&(thread->replies), new_reply, entries);

    return new_reply;
}

void list_threads(database_t* db)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(db->threads), entries)
    {
        printf("Thread UUID: %s\n", thread->uuid);
        printf("Thread Title: %s\n", thread->title);
        printf("Thread Message: %s\n", thread->message);
        printf("Thread Related Channel UUID: %s\n",
               thread->related_channel_uuid);
        printf("Thread Creator UUID: %s\n", thread->creator_uuid);
        printf("Thread Created At: %s", ctime(&(thread->created_at)));
        printf("Thread Replies:\n");

        reply_t* reply;
        LIST_FOREACH(reply, &(thread->replies), entries) {
            printf("    Reply UUID: %s\n", reply->uuid);
            printf("    Reply Body: %s\n", reply->body);
            printf("    Reply Created At: %s", ctime(&(reply->created_at)));
            printf("    Reply Related Thread UUID: %s\n",
                   reply->related_thread_uuid);
        }

        printf("\n");
    }
}

void free_all_threads(database_t* db)
{
    thread_t* thread;
    thread_t* tmp_thread;

    LIST_FOREACH_SAFE(thread, &(db->threads), entries, tmp_thread) {
        reply_t* reply;
        reply_t* tmp_reply;

        LIST_FOREACH_SAFE(reply, &(thread->replies), entries, tmp_reply) {
            LIST_REMOVE(reply, entries);
            free(reply);
        }

        LIST_REMOVE(thread, entries);
        free(thread);
    }
}

void list_replies_for_thread(database_t* db, char* thread_uuid)
{
    thread_t* thread = find_thread_by_uuid(db, thread_uuid);

    if (thread == NULL) {
        printf("Error: Thread not found\n");
        return;
    }

    printf("Replies for thread '%s':\n", thread->title);

    reply_t* reply;
    LIST_FOREACH(reply, &(thread->replies), entries) {
        printf("- %s: %s %s\n", reply->uuid, reply->body, ctime(&(reply->created_at)));
    }
}
