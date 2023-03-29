/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_replies.c
*/

#include "../../../include/server.h"

static void append_replies_json(database_t* db, thread_t* thread, char* json)
{
    strncat(json,
            "  \"status\": 231,\n"
            "  \"message\": \"Replies list\",\n"
            "  \"replies\": [\n",
            BUFFER_SIZE - strlen(json) - 1);

    reply_t* reply;
    LIST_FOREACH(reply, &(thread->replies), entries) {
        char reply_json[BUFFER_SIZE];
        snprintf(reply_json, BUFFER_SIZE,
        "\t{\n\t  \"reply_uuid\": \"%s\",\n\t  \"reply_body\": "
        "\"%s\",\n\t  \"timestamp\": \"%ld\"\n\t},\n",
        reply->uuid, reply->body, (long)reply->created_at);
        strncat(json, reply_json, BUFFER_SIZE - strlen(json) - 1);
    }
    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
    strncat(json, "  ]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* list_replies_for_thread(database_t* db, char* thread_uuid)
{
    thread_t* thread = find_thread_by_uuid(db, thread_uuid);

    if (thread == NULL)
        return NULL;

    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_replies_json(db, thread, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
