/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_discussions.c
*/

#include "../../include/server.h"

void load_discussions_from_file(database_t *db)
{
    FILE *file = open_file("discussions.json", "r");
    if (!file) return;

    char line[256];
    discussion_t* current_discussion = NULL;
    message_t* current_message = NULL;

    LIST_INIT(&db->discussions);

    while (fgets(line, sizeof(line), file)) {
          if (strstr(line, "{")) {
            if (current_discussion) {
                current_message = malloc(sizeof(message_t));
                LIST_INSERT_HEAD(&current_discussion->messages,
                                 current_message, entries);
            } else {
                current_discussion = malloc(sizeof(discussion_t));
                LIST_INSERT_HEAD(&db->discussions, current_discussion, entries);
                LIST_INIT(&current_discussion->messages);
            }
        } else if (strstr(line, "}")) {
            if (current_message) {
                current_message = NULL;
            } else {
                current_discussion = NULL;
            }
        } else if (current_discussion) {
            char key[64], value[256];
            sscanf(line, " \"%[^\"]\": \"%[^\"]\"", key, value);

            if (strcmp(key, "uuid") == 0) {
                if (current_message) {
                    strcpy(current_message->uuid, value);
                } else {
                    strcpy(current_discussion->uuid, value);
                }
            } else if (strcmp(key, "sender_uuid") == 0) {
                strcpy(current_discussion->sender_uuid, value);
            } else if (strcmp(key, "receiver_uuid") == 0) {
                strcpy(current_discussion->receiver_uuid, value);
            } else if (strcmp(key, "body") == 0) {
                strcpy(current_message->body, value);
            } else if (strcmp(key, "sender_uuid") == 0) {
                strcpy(current_message->sender_uuid, value);
            }
        }
    }

    fclose(file);
}
