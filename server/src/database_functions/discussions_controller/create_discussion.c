/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_discussion.c
*/

#include "../../../include/server.h"

static discussion_t* create_disc_obj(char* sender_uuid, char* receiver_uuid)
{
    discussion_t* new_discussion = (discussion_t*)malloc(sizeof(discussion_t));

    if (new_discussion == NULL) {
        printf("Error: Failed to allocate memory for new discussion\n");
        return NULL;
    }

    char* discussion_uuid = generate_uuid();

    strncpy(new_discussion->uuid, discussion_uuid, MAX_UUID_LENGTH);
    strncpy(new_discussion->sender_uuid, sender_uuid, MAX_UUID_LENGTH);
    strncpy(new_discussion->receiver_uuid, receiver_uuid, MAX_UUID_LENGTH);

    free(discussion_uuid);

    printf("New discussion created with UUID: %s\n", new_discussion->uuid);

    LIST_INIT(&(new_discussion->messages));

    return new_discussion;
}

discussion_t* create_discussion(database_t* db, char* sender_uuid,
char* receiver_uuid)
{
    discussion_t* discussion =
        find_discussion_by_users(db, sender_uuid, receiver_uuid);

    if (discussion) {
        printf("Error: Discussion already exists\n");
        return discussion;
    }

    discussion_t* new_discussion = create_disc_obj(sender_uuid, receiver_uuid);

    if (!new_discussion)
        return NULL;

    LIST_INSERT_HEAD(&(db->discussions), new_discussion, entries);
    printf("New discussion created with UUID: %s\n", new_discussion->uuid);
    return new_discussion;
}

message_t* create_message_obj(char* message_body, char* sender_uuid)
{
    message_t* new_message = malloc(sizeof(message_t));

    if (!new_message) {
        printf("Error: Failed to allocate memory for new message\n");
        return NULL;
    }

    char* message_uuid = generate_uuid();

    strncpy(new_message->uuid, message_uuid, MAX_UUID_LENGTH);
    strncpy(new_message->body, message_body, MAX_BODY_LENGTH);
    strncpy(new_message->sender_uuid, sender_uuid, MAX_UUID_LENGTH);
    new_message->created_at = time(NULL);

    free(message_uuid);

    return new_message;
}

bool add_message_to_discussion(database_t* db, char* sender_uuid,
char* receiver_uuid, char* message_body)
{
    discussion_t* discussion =
        find_discussion_by_users(db, sender_uuid, receiver_uuid);

    if (!discussion) {
        printf("Error(add_message_to_discussion): Discussion not found\n");
        return false;
    }

    message_t* new_message = create_message_obj(message_body, sender_uuid);

    if (new_message == NULL)
        return false;

    LIST_INSERT_HEAD(&(discussion->messages), new_message, entries);

    return true;
}
