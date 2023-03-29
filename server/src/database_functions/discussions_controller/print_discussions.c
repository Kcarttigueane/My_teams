/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_discussions.c
*/

#include "../../../include/server.h"

static void append_messages(database_t* db, discussion_t* discussion,
char* json)
{
    message_t* message;

    LIST_FOREACH(message, &(discussion->messages), entries) {
        char message_json[BUFFER_SIZE];
        snprintf(message_json, BUFFER_SIZE,
        "\t{\n\t  \"message_body\": \"%s\",\n\t  \"timestamp\": "
        "\"%ld\"\n\t},\n",
        message->body, (long)message->created_at);
        strncat(json, message_json, BUFFER_SIZE - strlen(json) - 1);
    }

    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
}

static void append_messages_json(database_t* db, discussion_t* discussion,
char* json)
{
    strncat(json,
    "  \"status\": 212,\n"
    "  \"message\": \"Message list\",\n"
    "  \"recipient_uuid\": \"user_uuid\",\n"
    "  \"messages\": [\n",
    BUFFER_SIZE - strlen(json) - 1);
    append_messages(db, discussion, json);
    strncat(json, "  \n]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* list_discussion_messages(database_t* db, discussion_t *discussion)
{
    char* json = (char *)malloc(BUFFER_SIZE * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    debug_discussion(discussion);

    snprintf(json, BUFFER_SIZE, "{\n");
    append_messages_json(db, discussion, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
