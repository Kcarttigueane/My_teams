/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** discussions.c
*/

#include "../../../include/server.h"

static void append_threads(database_t* db, char* json, char* channel_uuid)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(db->threads), entries) {
        if (strcmp(thread->related_channel_uuid, channel_uuid) == 0) {
            char thread_json[BUFFER_SIZE];
            snprintf(thread_json, BUFFER_SIZE,
            "\t{\n\t  \"thread_uuid\": \"%s\",\n\t  \"thread_title\": "
            "\"%s\",\n\t  \"thread_message\": \"%s\",\n\t  "
            "\"related_channel_uuid\": \"%s\",\n\t  "
            "\"creator_uuid\": \"%s\",\n\t  "
            "\"created_at\": \"%ld\"\n\t}",
            thread->uuid, thread->title, thread->message,
            thread->related_channel_uuid, thread->creator_uuid,
            (long)thread->created_at);
            strncat(json, thread_json, BUFFER_SIZE - strlen(json) - 1);
        }
    }
}

static void append_threads_json(database_t* db, char* json, char* channel_uuid)
{
    strncat(json,
            "  \"status\": 230,\n"
            "  \"message\": \"Threads list\",\n"
            "  \"threads\": [\n",
            BUFFER_SIZE - strlen(json) - 1);
    append_threads(db, json, channel_uuid);
    strncat(json, "   \n  ]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* list_threads(database_t* db, char *channel_uuid)
{
    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_threads_json(db, json, channel_uuid);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
