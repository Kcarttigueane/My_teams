/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** msgs.c
*/

#include "../../include/server.h"

static void append_messages(discussion_t* discussion, char* json)
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

static void append_messages_json(discussion_t* discussion, char* json)
{
    strncat(json,
            "  \"status\": 221,\n"
            "  \"message\": \"Message list\",\n"
            "  \"messages\": [\n",
            BUFFER_SIZE - strlen(json) - 1);
    append_messages(discussion, json);
    strncat(json, "  \n]\n", BUFFER_SIZE - strlen(json) - 1);
}

void msgs(list_args_t* args)
{
    remove_quotes(args->split_command[1]);
    discussion_t* discussion = find_discussion_by_users(
        args->db, args->client->current_user_uuid, args->split_command[1]);

    if (discussion == NULL) {
        send_json_error_response(args->client->socket_fd, 530,
        "Discussion not found");
        return;
    }
    char* json = malloc(BUFFER_SIZE * sizeof(char));
    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return;
    }
    snprintf(json, BUFFER_SIZE, "{\n");
    append_messages_json(discussion, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    send(args->client->socket_fd, json, strlen(json), 0);
    free(json);
}
