/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** discussion.c
*/

#include "../../include/server.h"

discussion_t* find_discussion_by_users(database_t* database, char* sender_uuid,
char* receiver_uuid)
{
    discussion_t* discussion;

    LIST_FOREACH(discussion, &(database->discussions), entries) {
        printf("Discussion: %s, %s, %s\n", discussion->uuid, discussion->sender_uuid, discussion->receiver_uuid);
        if ((!strcmp(discussion->sender_uuid, sender_uuid) && !strcmp(discussion->receiver_uuid, receiver_uuid)) ||
            (!strcmp(discussion->sender_uuid, receiver_uuid) && !strcmp(discussion->receiver_uuid, sender_uuid))) {
            return discussion;
        }
    }
    return NULL;
}

discussion_t* find_discussion_by_uuid(database_t* database, char* uuid)
{
    discussion_t* discussion;

    LIST_FOREACH(discussion, &(database->discussions), entries) {
        if (!strcmp(discussion->uuid, uuid))
            return discussion;
    }
    return NULL;
}

discussion_t *create_discussion_obj(char *sender_uuid, char *receiver_uuid)
{
    discussion_t *new_discussion = malloc(sizeof(discussion_t));

    if (new_discussion == NULL) {
        printf("Error: Failed to allocate memory for new discussion\n");
        return NULL;
    }

    char *discussion_uuid = generate_uuid();

    strncpy(new_discussion->uuid, discussion_uuid, MAX_UUID_STR_LEN);
    strncpy(new_discussion->sender_uuid, sender_uuid, MAX_UUID_STR_LEN);
    strncpy(new_discussion->receiver_uuid, receiver_uuid, MAX_UUID_STR_LEN);

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

    // ! Check if the receiver UUID exists in the database =>  Dont think we need it here
    // user_t* receiver = find_user_by_uuid(db, receiver_uuid);
    // if (receiver == NULL) {
    //     printf("Error: Receiver UUID does not exist in the database\n");
    //     return NULL;
    // }

    discussion_t* new_discussion = create_discussion_obj(sender_uuid,
    receiver_uuid);

    if (new_discussion == NULL)  {
        printf("Error: Failed to create discussion\n");
        return NULL;
    }

    LIST_INSERT_HEAD(&(db->discussions), new_discussion, entries);
    printf("New discussion created with UUID: %s\n", new_discussion->uuid);
    return new_discussion;
}

message_t *create_message_obj(char *message_body, char *sender_uuid)
{
    message_t *new_message = malloc(sizeof(message_t));

    if (new_message == NULL) {
        printf("Error: Failed to allocate memory for new message\n");
        return NULL;
    }

    char *message_uuid = generate_uuid();

    strncpy(new_message->uuid, message_uuid, MAX_UUID_STR_LEN);
    strncpy(new_message->body, message_body, MAX_BODY_LENGTH);
    strncpy(new_message->sender_uuid, sender_uuid, MAX_UUID_STR_LEN);
    new_message->created_at = time(NULL);

    free(message_uuid);

    return new_message;
}

bool add_message_to_discussion(database_t* db, char* sender_uuid,
char* receiver_uuid, char* message_body)
{
    discussion_t* discussion =
        find_discussion_by_users(db, sender_uuid, receiver_uuid);

    if (discussion == NULL) {
        printf("Error: Discussion not found\n");
        return false;
    }

    message_t* new_message = create_message_obj(message_body, sender_uuid);
    if (new_message == NULL)
        return false;

    LIST_INSERT_HEAD(&(discussion->messages), new_message, entries);

    return true;
}

void free_discussions(database_t* db)
{
    discussion_t* discussion;
    discussion_t* tmp_discussion;

    LIST_FOREACH_SAFE(discussion, &(db->discussions), entries, tmp_discussion)
    {
        message_t* message;
        message_t* tmp_message;

        LIST_FOREACH_SAFE(message, &(discussion->messages), entries,
        tmp_message)
        {
            LIST_REMOVE(message, entries);
            free(message);
        }

        LIST_REMOVE(discussion, entries);
        free(discussion);
    }
}

void free_discussion(discussion_t* discussion)
{
    LIST_REMOVE(discussion, entries);

    message_t* message;
    message_t* tmp_message;

    LIST_FOREACH_SAFE(message, &(discussion->messages), entries, tmp_message)
    {
        LIST_REMOVE(message, entries);
        free(message);
    }
    free(discussion);
}

void print_discussion_details(database_t* db, char* discussion_uuid)
{
    discussion_t* discussion = find_discussion_by_uuid(db, discussion_uuid);

    if (discussion == NULL) {
        printf("Error: Discussion not found\n");
        return;
    }

    printf("Discussion UUID: %s\n", discussion->uuid);
    printf("Sender UUID: %s\n", discussion->sender_uuid);
    printf("Receiver UUID: %s\n", discussion->receiver_uuid);
    printf("Messages:\n");

    message_t* message;
    LIST_FOREACH(message, &(discussion->messages), entries) {
        printf(" - %s\n", message->body);
        printf("   Sender UUID: %s\n", message->sender_uuid);
        printf("   Created at: %s", ctime(&(message->created_at)));
    }
}

void print_all_messages_in_discussion(database_t* db, char* discussion_uuid)
{
    discussion_t* discussion = find_discussion_by_uuid(db, discussion_uuid);

    if (discussion == NULL) {
        printf("Error: Discussion not found\n");
        return;
    }

    printf("Messages in discussion with UUID %s:\n", discussion->uuid);

    message_t* message;
    LIST_FOREACH(message, &(discussion->messages), entries) {
        printf(" - %s\n", message->body);
        printf("   Sender UUID: %s\n", message->sender_uuid);
        printf("   Created at: %s", ctime(&(message->created_at)));
    }
}
