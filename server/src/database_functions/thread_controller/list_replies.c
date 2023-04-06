/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_replies.c
*/

#include "../../../include/server.h"

static void append_empty_replies_json(char* json)
{
    strncat(json,
            "  \"status\": 230,\n"
            "  \"message\": \"Replies list\"\n",
            BUFFER_SIZE - strlen(json) - 1);
}

static void append_single_reply_json(reply_t* reply, char* json)
{
    char reply_json[BUFFER_SIZE];
    char *timestamp = timestamp_to_string(reply->created_at);
    snprintf(reply_json, BUFFER_SIZE,
    "\t{\n\t  \"reply_uuid\": \"%s\",\n\t  \"reply_body\": "
    "\"%s\",\n\t  \"creator_uuid\": \"%s\",\n\t  \"timestamp\": "
    "\"%s\"\n\t},\n",
    reply->uuid, reply->body, reply->creator_uuid, timestamp);
    strncat(json, reply_json, BUFFER_SIZE - strlen(json) - 1);
    free(timestamp);
}

static void append_replies_json(thread_t* thread, char* json)
{
    if (thread->replies.lh_first == NULL) {
        append_empty_replies_json(json);
        return;
    }
    strncat(json,
            "  \"status\": 231,\n"
            "  \"message\": \"Replies list\",\n"
            "  \"replies\": [\n",
            BUFFER_SIZE - strlen(json) - 1);
    reply_t* reply;
    LIST_FOREACH(reply, &(thread->replies), entries) {
        append_single_reply_json(reply, json);
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

    if (!thread)
        return NULL;

    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_replies_json(thread, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
