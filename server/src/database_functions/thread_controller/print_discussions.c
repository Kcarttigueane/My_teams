/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** discussions.c
*/

#include "../../../include/server.h"

void list_threads(database_t* db)
{
    thread_t* thread;
    LIST_FOREACH(thread, &(db->threads), entries) {
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
