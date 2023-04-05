/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_threads.c
*/

#include "../../../include/server.h"

void save_reply(FILE* file, reply_t* reply)
{
    fprintf(file, "      {\n");
    fprintf(file, "        \"uuid\": \"%s\",\n", reply->uuid);
    fprintf(file, "        \"body\": \"%s\",\n", reply->body);
    fprintf(file, "        \"related_thread_uuid\": \"%s\"\n",
            reply->related_thread_uuid);
    fprintf(file, "        \"creator_uuid\": \"%s\",\n", reply->creator_uuid);
    fprintf(file, "      }");
}

void save_replies(FILE* file, thread_t* thread)
{
    fprintf(file, "    \"replies\": [\n");
    reply_t* reply;
    bool first_reply = true;
    LIST_FOREACH(reply, &(thread->replies), entries) {
        if (!first_reply) {
            fprintf(file, ",\n");
        }
        first_reply = false;
        save_reply(file, reply);
    }
    fprintf(file, "\n    ]\n");
}

void save_thread(FILE* file, thread_t* thread)
{
    fprintf(file, "  {\n");
    fprintf(file, "    \"uuid\": \"%s\",\n", thread->uuid);
    fprintf(file, "    \"title\": \"%s\",\n", thread->title);
    fprintf(file, "    \"message\": \"%s\",\n", thread->message);
    fprintf(file, "    \"related_channel_uuid\": \"%s\",\n",
    thread->related_channel_uuid);
    fprintf(file, "    \"creator_uuid\": \"%s\",\n", thread->creator_uuid);
    fprintf(file, "    \"created_at\": \"%ld\",\n", thread->created_at);
    save_replies(file, thread);
    fprintf(file, " }");
}

void save_threads_to_file(database_t* db)
{
    if (!is_thread_list_empty(db)) return;

    FILE* file = open_file("libs/database/threads.json", "w");

    if (!file) return;

    fprintf(file, "[\n");
    thread_t* thread;
    bool first_thread = true;

    LIST_FOREACH(thread, &(db->threads), entries) {
        if (!first_thread) {
            fprintf(file, ",\n");
        }
        first_thread = false;
        save_thread(file, thread);
    }
    fprintf(file, "\n]\n");

    fclose(file);
}
