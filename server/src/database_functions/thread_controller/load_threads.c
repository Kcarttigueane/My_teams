/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_threads.c
*/

#include "../../../include/server.h"

void load_threads_from_file(database_t* db)
{
    FILE* file = open_file("libs/database/threads.json", "r");
    if (!file)
        return;

    char line[256];
    thread_t* current_thread = NULL;
    reply_t* current_reply = NULL;

    LIST_INIT(&db->threads);

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "{")) {
            if (current_thread) {
                current_reply = malloc(sizeof(reply_t));
                LIST_INSERT_HEAD(&current_thread->replies, current_reply,
                                 entries);
            } else {
                current_thread = malloc(sizeof(thread_t));
                LIST_INSERT_HEAD(&db->threads, current_thread, entries);
                LIST_INIT(&current_thread->replies);
            }
        } else if (strstr(line, "}")) {
            if (current_reply) {
                current_reply = NULL;
            } else {
                current_thread = NULL;
            }
        } else if (current_thread) {
            char key[64], value[256];
            sscanf(line, " \"%[^\"]\": \"%[^\"]\"", key, value);

            if (strcmp(key, "uuid") == 0) {
                if (current_reply) {
                    strcpy(current_reply->uuid, value);
                } else {
                    strcpy(current_thread->uuid, value);
                }
            } else if (strcmp(key, "title") == 0) {
                strcpy(current_thread->title, value);
            } else if (strcmp(key, "message") == 0) {
                strcpy(current_thread->message, value);
            } else if (strcmp(key, "related_channel_uuid") == 0) {
                strcpy(current_thread->related_channel_uuid, value);
            } else if (strcmp(key, "creator_uuid") == 0) {
                strcpy(current_thread->creator_uuid, value);
            } else if (strcmp(key, "body") == 0) {
                strcpy(current_reply->body, value);
            } else if (strcmp(key, "related_thread_uuid") == 0) {
                strcpy(current_reply->related_thread_uuid, value);
            }
        }
    }

    fclose(file);
}
