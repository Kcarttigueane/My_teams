/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_thread.c
*/

#include "../../../include/server.h"

static thread_t *create_thread_obj(create_thread_params_t *params)
{
    thread_t *new_thread = (thread_t *)malloc(sizeof(thread_t));

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

    return new_thread;
}

thread_t* create_thread(database_t* db, create_thread_params_t* params)
{
    thread_t* new_thread = create_thread_obj(params);

    if (new_thread == NULL)
        return NULL;

    LIST_INIT(&(new_thread->replies));

    LIST_INSERT_HEAD(&(db->threads), new_thread, entries);

    return new_thread;
}

static reply_t* create_reply_obj(char* thread_uuid, char* reply_body,
char* user_uuid)
{
    reply_t* new_reply = (reply_t *)malloc(sizeof(reply_t));

    if (new_reply == NULL) {
        printf("Error: Failed to allocate memory for new reply\n");
        return NULL;
    }

    char* reply_uuid = generate_uuid();

    strncpy(new_reply->uuid, reply_uuid, MAX_UUID_STR_LEN);
    strncpy(new_reply->body, reply_body, MAX_BODY_LENGTH);
    strncpy(new_reply->related_thread_uuid, thread_uuid, MAX_UUID_STR_LEN);
    new_reply->created_at = time(NULL);

    free(reply_uuid);

    return new_reply;
}

reply_t* add_reply_to_thread(database_t* db, char* thread_uuid,
char* reply_body, char* user_uuid)
{
    thread_t* thread = find_thread_by_uuid(db, thread_uuid);

    if (thread == NULL) {
        printf("Error: Thread not found\n");
        return NULL;
    }

    reply_t* new_reply = create_reply_obj(thread_uuid, reply_body, user_uuid);

    if (new_reply == NULL)
        return NULL;

    LIST_INSERT_HEAD(&(thread->replies), new_reply, entries);

    return new_reply;
}
