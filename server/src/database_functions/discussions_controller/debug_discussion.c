/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** debug_discussion.c
*/

#include "../../../include/server.h"
#include "../../../../include/color.h"

void debug_discussion(discussion_t* new_discussion)
{
    printf(RED);
    printf("[Discussion] %s\n", CLIENT_PROMPT);
    printf(YELLOW);
    printf("\t\t[UUID] %s\n", new_discussion->uuid);
    printf("\t\t[Sender UUID] %s\n", new_discussion->sender_uuid);
    printf("\t\t[Receiver UUID] %s\n", new_discussion->receiver_uuid);

    message_t* message;

    LIST_FOREACH(message, &(new_discussion->messages), entries) {
        printf(" - %s\n", message->body);
        printf("   Sender UUID: %s\n", message->sender_uuid);
        printf("   Created at: %s", ctime(&(message->created_at)));
    }
    printf(RESET);
}
