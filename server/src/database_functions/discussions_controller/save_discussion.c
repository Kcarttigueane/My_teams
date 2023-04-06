/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_discussion.c
*/

#include "../../../include/server.h"

void save_message(FILE* file, message_t* message)
{
    char *timestamp = timestamp_to_string(message->created_at);

    fprintf(file, "      {\n");
    fprintf(file, "        \"uuid\": \"%s\",\n", message->uuid);
    fprintf(file, "        \"body\": \"%s\",\n", message->body);
    fprintf(file, "        \"sender_uuid\": \"%s\",\n", message->sender_uuid);
    fprintf(file, "        \"created_at\": \"%s\"\n", timestamp);
    fprintf(file, "      }");

    free(timestamp);
}

void save_discussion(FILE* file, discussion_t* discussion)
{
    fprintf(file, "  {\n");
    fprintf(file, "    \"uuid\": \"%s\",\n", discussion->uuid);
    fprintf(file, "    \"sender_uuid\": \"%s\",\n", discussion->sender_uuid);
    fprintf(file, "    \"receiver_uuid\": \"%s\",\n",
    discussion->receiver_uuid);
    fprintf(file, "    \"messages\": [\n");

    message_t* message;
    bool first_message = true;

    LIST_FOREACH(message, &(discussion->messages), entries) {
        if (!first_message)
            fprintf(file, ",\n");
        first_message = false;

        save_message(file, message);
    }

    fprintf(file, "\n    ]\n");
    fprintf(file, "  }");
}

void save_discussions_to_file(database_t* db)
{
    if (!is_dis_list_empty(db)) return;
    FILE* file = open_file("libs/database/discussions.json", "w");
    if (!file) return;

    fprintf(file, "[\n");

    discussion_t* discussion;
    bool first_discussion = true;

    LIST_FOREACH(discussion, &(db->discussions), entries) {
        if (!first_discussion)
            fprintf(file, ",\n");

        first_discussion = false;

        save_discussion(file, discussion);
    }

    fprintf(file, "\n]\n");
    fclose(file);
}
