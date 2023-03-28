/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_discussions.c
*/

#include "../../../include/server.h"

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
