/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** find_discussions.c
*/

#include "../../../include/server.h"

thread_t* find_thread_by_uuid(database_t* database, char* uuid)
{
    thread_t* thread;

    LIST_FOREACH(thread, &(database->threads), entries) {
        if (!strcmp(thread->uuid, uuid))
            return thread;
    }
    printf("Error: Thread not found\n");
    return NULL;
}
