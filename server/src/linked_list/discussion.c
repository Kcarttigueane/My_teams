/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** discussion.c
*/

#include "../../include/server.h"

// Initialize the discussions list
LIST_HEAD(discussion_list, discussion_s) discussions_head = LIST_HEAD_INITIALIZER(discussions_head);

// Create a new discussion
discussion_t* create_discussion(char* sender_uuid, char* receiver_uuid)
{
    // Check if the discussion already exists
    discussion_t* discussion;
    LIST_FOREACH(discussion, &discussions_head, entries)
    {
        if (strcmp(discussion->sender->uuid, sender_uuid) == 0 &&
            strcmp(discussion->receiver->uuid, receiver_uuid) == 0) {
            printf("Error: Discussion already exists\n");
            return NULL;
        }
    }

    // Create new sender and receiver user nodes
    user_t* sender = get_user_by_uuid(sender_uuid);
    if (sender == NULL) {
        printf("Error: Sender with UUID %s not found\n", sender_uuid);
        return NULL;
    }

    user_t* receiver = get_user_by_uuid(receiver_uuid);
    if (receiver == NULL) {
        printf("Error: Receiver with UUID %s not found\n", receiver_uuid);
        return NULL;
    }

    // Create a new discussion node
    discussion_t* new_discussion = malloc(sizeof(discussion_t));
    if (new_discussion == NULL) {
        printf("Error: Failed to allocate memory for new discussion\n");
        return NULL;
    }

    strncpy(new_discussion->uuid, generate_uuid(), MAX_UUID_STR_LEN);
    new_discussion->sender = sender;
    new_discussion->receiver = receiver;
    new_discussion->messages = NULL;

    // Add the new discussion node to the linked list
    LIST_INSERT_HEAD(&discussions_head, new_discussion, entries);

    return new_discussion;
}

// Delete a discussion by sender and receiver UUIDs
void delete_discussion(char* sender_uuid, char* receiver_uuid)
{
    discussion_t* discussion;
    LIST_FOREACH(discussion, &discussions_head, entries)
    {
        if (strcmp(discussion->sender->uuid, sender_uuid) == 0 &&
            strcmp(discussion->receiver->uuid, receiver_uuid) == 0) {
            // Remove the discussion node from the linked list
            LIST_REMOVE(discussion, entries);

            // Free the discussion node and its messages
            message_t* message;
            while ((message = LIST_FIRST(&discussion->messages)) != NULL) {
                LIST_REMOVE(message, entries);
                free(message);
            }
            free(discussion);

            printf("Discussion deleted between %s and %s\n", sender_uuid,
                   receiver_uuid);
            return;
        }
    }
    printf("Discussion not found between %s and %s\n", sender_uuid,
           receiver_uuid);
}

// Find a discussion by sender and receiver UUIDs
discussion_t* find_discussion(char* sender_uuid, char* receiver_uuid)
{
    discussion_t* discussion;
    LIST_FOREACH(discussion, &discussions_head, entries)
    {
        if (strcmp(discussion->sender->uuid, sender_uuid) == 0 &&
            strcmp(discussion->receiver->uuid, receiver_uuid) == 0) {
            return discussion;
        }
    }
    return NULL;
}

// Add a message to a discussion
bool add_message_to_discussion(char* sender_uuid, char* receiver_uuid,
                               char* message_body)
{
    // Find the discussion
    discussion_t* discussion_ptr = find_discussion(sender_uuid, receiver_uuid);

    // If the discussion doesn't exist, create a new one
    if (discussion_ptr == NULL) {
        if (!add_discussion(sender_uuid, receiver_uuid)) {
            printf("Error: Failed to add new discussion\n");
            return false;
        }
        discussion_ptr = find_discussion(sender_uuid, receiver_uuid);
    }

    // Create a new message node
    message_t* new_message = malloc(sizeof(message_t));

    if (new_message == NULL) {
        printf("Error: Failed to allocate memory for new message\n");
        return false;
    }
    generate_uuid(new_message->uuid, MAX_UUID_STR_LEN);
    strncpy(new_message->body, message_body, MAX_BODY_LENGTH);

    // Add the new message node to the linked list of messages in the discussion
    LIST_INSERT_HEAD(&discussion_ptr->messages, new_message, entries);

    return true;
}
