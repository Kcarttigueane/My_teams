/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** discussions.c
*/

#include "../../../include/server.h"

static void append_threads(database_t* db, char* json, char* channel_uuid,
int *nb_threads)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(db->threads), entries) {
        if (strcmp(thread->related_channel_uuid, channel_uuid) == 0) {
            char* timestamp = timestamp_to_string(thread->created_at);
            char thread_json[BUFFER_SIZE];
            snprintf(thread_json, BUFFER_SIZE,
            "\t{\n\t  \"thread_uuid\": \"%s\",\n\t  \"thread_title\": "
            "\"%s\",\n\t  \"thread_message\": \"%s\",\n\t  "
            "\"related_channel_uuid\": \"%s\",\n\t  "
            "\"creator_uuid\": \"%s\",\n\t  "
            "\"created_at\": \"%s\"\n\t}",
            thread->uuid, thread->title, thread->message,
            thread->related_channel_uuid, thread->creator_uuid, timestamp);
            strncat(json, thread_json, BUFFER_SIZE - strlen(json) - 1);
            *nb_threads += 1;
        }
    }
}

static bool append_threads_json(database_t* db, char* json, char* channel_uuid)
{
    int nb_threads = 0;
    strncat(json,
            "  \"status\": 210,\n"
            "  \"message\": \"Threads list\",\n"
            "  \"threads\": [\n",
            BUFFER_SIZE - strlen(json) - 1);
    append_threads(db, json, channel_uuid, &nb_threads);
    if (nb_threads == 0) {
        return false;
    }
    strncat(json, "   \n  ]\n", BUFFER_SIZE - strlen(json) - 1);
    return true;
}

char* list_threads(database_t* db, char *channel_uuid)
{
    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (!json) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    if (!append_threads_json(db, json, channel_uuid)) {
        memset(json, 0, BUFFER_SIZE);
        snprintf(json, BUFFER_SIZE, "{\n");
        strncat(json,
        "  \"status\": 210,\n"
        "  \"message\": \"Threads list\",\n",
        BUFFER_SIZE - strlen(json) - 1);
    }
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
