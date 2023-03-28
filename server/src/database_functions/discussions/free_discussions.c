/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** free_discussions.c
*/

#include "../../../include/server.h"

void free_discussions(database_t* db)
{
    discussion_t* discussion;
    discussion_t* tmp_discussion;

    LIST_FOREACH_SAFE(discussion, &(db->discussions), entries, tmp_discussion) {
        message_t* message;
        message_t* tmp_message;

        LIST_FOREACH_SAFE(message, &(discussion->messages), entries,
        tmp_message) {
            LIST_REMOVE(message, entries);
            free(message);
        }

        LIST_REMOVE(discussion, entries);
        free(discussion);
    }
}

void free_discussion(discussion_t* discussion)
{
    LIST_REMOVE(discussion, entries);

    message_t* message;
    message_t* tmp_message;

    LIST_FOREACH_SAFE(message, &(discussion->messages), entries, tmp_message) {
        LIST_REMOVE(message, entries);
        free(message);
    }
    free(discussion);
}
