/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** debug_thread.c
*/

#include "../../../include/server.h"
#include "../../../../include/color.h"

void debug_thread(thread_t* new_thread)
{
    printf(RED);
    printf("[Thread] %s\n", CLIENT_PROMPT);
    printf(YELLOW);
    printf("\t\t[UUID] %s\n", new_thread->uuid);
    printf("\t\t[Title] %s\n", new_thread->title);
    printf("\t\t[Message] %s\n", new_thread->message);
    printf("\t\t[Related Channel UUID] %s\n", new_thread->related_channel_uuid);
    printf("\t\t[Creator UUID] %s\n", new_thread->creator_uuid);
    printf("\t\t[Created at] %s", ctime(&(new_thread->created_at)));

    reply_t* reply;

    LIST_FOREACH(reply, &(new_thread->replies), entries) {
        printf("\t\t[Reply] %s\n", CLIENT_PROMPT);
        printf("\t\t\t[UUID] %s\n", reply->uuid);
        printf("\t\t\t[Body] %s\n", reply->body);
        printf("\t\t\t[Creator UUID] %s\n", reply->creator_uuid);
        printf("\t\t\t[Related Thread UUID] %s\n", reply->related_thread_uuid);
        printf("\t\t\t[Created at] %s", ctime(&(reply->created_at)));
    }
}
