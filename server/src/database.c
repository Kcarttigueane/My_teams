/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** database.c
*/

#include <sys/queue.h>
#include "../include/server.h"

database_t init_database(void)
{
    database_t database = {
        .teams = LIST_HEAD_INITIALIZER(database.teams),
        .channels = LIST_HEAD_INITIALIZER(database.channels),
        .threads = LIST_HEAD_INITIALIZER(database.threads),
        .discussions = LIST_HEAD_INITIALIZER(database.discussions),
        .users = LIST_HEAD_INITIALIZER(database.users),
    };
    return database;
}

void free_database(database_t* database)
{
    free_teams(database);
    free_channels(database);
    free_all_threads(database);
    free_discussions(database);
    free_users(database);
}
