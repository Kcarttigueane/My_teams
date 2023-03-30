/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** load_discussions.c
*/

#include "../../../include/server.h"

static void handle_curly_brace(database_t* db,
discussion_t** current_discussion, message_t** current_message)
{
    if (*current_discussion) {
        *current_message = (message_t*)calloc(1, sizeof(message_t));
        LIST_INSERT_HEAD(&(*current_discussion)->messages, *current_message,
        entries);
    } else {
        *current_discussion = (discussion_t*)calloc(1, sizeof(discussion_t));
        LIST_INSERT_HEAD(&db->discussions, *current_discussion, entries);
        LIST_INIT(&(*current_discussion)->messages);
    }
}

static void handle_closing_brace(discussion_t** current_discussion,
message_t** current_message)
{
    if (*current_message) {
        *current_message = NULL;
    } else {
        *current_discussion = NULL;
    }
}

static void handle_key_value_pairs(char* line, discussion_t* current_discussion,
message_t* current_message)
{
    char key[KEY_BUFFER] = {0}, value[256] = {0};
    int ret = sscanf(line, " \"%63[^\"]\": \"%255[^\"]\"", key, value);
    if (ret != 2) {
        return;
    }
    (!strcmp(key, "uuid"))
    ? (current_message ? strcpy(current_message->uuid, value)
    : strcpy(current_discussion->uuid, value))
    : (!strcmp(key, "sender_uuid")) &&
    current_discussion->sender_uuid[0] == '\0'
    ? strcpy(current_discussion->sender_uuid, value)
    : (!strcmp(key, "receiver_uuid"))
    ? strcpy(current_discussion->receiver_uuid, value)
    : (!strcmp(key, "body")) ? strcpy(current_message->body, value)
    : (!strcmp(key, "sender_uuid"))
    ? strcpy(current_message->sender_uuid, value)
    : (!strcmp(key, "timestamp"))
    ? (current_message->created_at = (time_t)atoi(value))
    : (void)0;
}

void load_discussions_from_file(database_t* db)
{
    FILE* file = open_file("libs/database/discussions.json", "r");
    if (!file)
        return;

    char line[256] = {0};
    discussion_t* current_discussion = NULL;
    message_t* current_message = NULL;

    LIST_INIT(&db->discussions);

    while (fgets(line, sizeof(line), file)) {
        strstr(line, "{")
        ? handle_curly_brace(db, &current_discussion, &current_message)
        : strstr(line, "}")
        ? handle_closing_brace(&current_discussion, &current_message)
        : handle_key_value_pairs(line, current_discussion, current_message);
    }

    fclose(file);
}
