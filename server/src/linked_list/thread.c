/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** thread.c
*/

#include "../../include/server.h"

thread_t* create_thread(database_t* db, char* title, char* message,
channel_t* channel, user_t* creator)
{
    thread_t* new_thread = (thread_t*)malloc(sizeof(thread_t));

    if (new_thread == NULL) {
        printf("Error: Failed to allocate memory for new thread\n");
        return NULL;
    }

    strncpy(new_thread->uuid, generate_uuid(), MAX_UUID_STR_LEN);
    strncpy(new_thread->title, title, MAX_NAME_LENGTH);
    strncpy(new_thread->message, message, MAX_BODY_LENGTH);
    new_thread->channel = channel;
    new_thread->creator = creator;

    LIST_INIT(&(new_thread->replies));

    LIST_INSERT_HEAD(&(db->threads), new_thread, entries);

    return new_thread;
}

thread_t* find_thread_by_uuid(database_t* database, char* uuid)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(database->threads), entries)
    {
        if (!strcmp(thread->uuid, uuid))
            return thread;
    }

    return NULL;
}

bool add_reply_to_thread(database_t* db, char* thread_uuid, char* reply_body,
                         user_t* user)
{
    thread_t* thread = find_thread_by_uuid(db, thread_uuid);

    if (thread == NULL) {
        printf("Error: Thread not found\n");
        return false;
    }

    reply_t* new_reply = malloc(sizeof(reply_t));
    if (new_reply == NULL) {
        printf("Error: Failed to allocate memory for new reply\n");
        return false;
    }

    strncpy(new_reply->uuid, generate_uuid(), MAX_UUID_STR_LEN);
    strncpy(new_reply->body, reply_body, MAX_BODY_LENGTH);
    strncpy(new_reply->related_thread_uuid, thread_uuid, MAX_UUID_STR_LEN);
    new_reply->user = user;

    LIST_INSERT_HEAD(&(thread->replies), new_reply, entries);

    return true;
}

void free_threads(database_t* db)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(db->threads), entries)
    {
        reply_t* reply;
        while ((reply = LIST_FIRST(&(thread->replies))) != NULL) {
            LIST_REMOVE(reply, entries);
            free(reply);
        }
        LIST_REMOVE(thread, entries);
        free(thread);
    }
}

bool is_thread_exist(database_t* db, char* thread_uuid)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(db->threads), entries)
    {
        if (!strcmp(thread->uuid, thread_uuid))
            return true;
    }

    return false;
}

void list_threads(database_t* db)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(db->threads), entries)
    {
        printf("Thread UUID: %s\n", thread->uuid);
        printf("Thread Title: %s\n", thread->title);
        printf("Thread Message: %s\n", thread->message);
        printf("Thread Channel UUID: %s\n", thread->channel->uuid);
        printf("Thread Creator UUID: %s\n", thread->creator->uuid);
        printf("Thread Replies:\n");

        reply_t* reply;
        LIST_FOREACH(reply, &(thread->replies), entries)
        {
            printf("    Reply UUID: %s\n", reply->uuid);
            printf("    Reply Body: %s\n", reply->body);
            printf("    Reply Related Thread UUID: %s\n",
                   reply->related_thread_uuid);
            printf("    Reply User UUID: %s\n", reply->user->uuid);
        }

        printf("\n");
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
    LIST_FOREACH(reply, &(thread->replies), entries)
    {
        printf("- %s: %s\n", reply->user->username, reply->body);
    }
}
