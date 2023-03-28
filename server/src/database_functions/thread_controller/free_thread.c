/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** free_thread.c
*/

#include "../../../include/server.h"

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
        printf("- %s: %s %s\n", reply->uuid, reply->body,
        ctime(&(reply->created_at)));
    }
}
