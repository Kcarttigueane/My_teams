/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** find_discussions.c
*/

#include "../../../include/server.h"

discussion_t* find_discussion_by_users(database_t* database, char* sender_uuid,
char* receiver_uuid)
{
    discussion_t* discussion;

    LIST_FOREACH(discussion, &(database->discussions), entries) {
        if ((!strcmp(discussion->sender_uuid, sender_uuid) &&
            !strcmp(discussion->receiver_uuid, receiver_uuid)) ||
            (!strcmp(discussion->sender_uuid, receiver_uuid) &&
            !strcmp(discussion->receiver_uuid, sender_uuid))) {
            return discussion;
        }
    }
    return NULL;
}

discussion_t* find_discussion_by_uuid(database_t* database, char* uuid)
{
    discussion_t* discussion;

    LIST_FOREACH(discussion, &(database->discussions), entries) {
        if (!strcmp(discussion->uuid, uuid))
            return discussion;
    }
    return NULL;
}
