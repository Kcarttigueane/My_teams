/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** database.c
*/

#include <sys/queue.h>
#include "../../include/server.h"

void save_database(database_t* database)
{
    save_teams_to_file(database);
    save_channels_to_file(database);
    save_threads_to_file(database);
    save_discussions_to_file(database);
    save_users_to_file(database);
}

static void load_database(database_t* database)
{
    load_teams_from_file(database);
    load_channels_from_file(database);
    load_threads_from_file(database);
    load_discussions_from_file(database);
    load_users_from_file(database);
}

database_t *init_database(void)
{
    database_t* database = (database_t*)calloc(1, sizeof(database_t));

    if (!database) return NULL;

    LIST_INIT(&database->users);
    LIST_INIT(&database->teams);
    LIST_INIT(&database->channels);
    LIST_INIT(&database->threads);
    LIST_INIT(&database->discussions);

    load_database(database);

    return database;
}

void free_database(database_t* database)
{
    free_teams(database);
    free_channels(database);
    free_all_threads(database);
    free_discussions(database);
    free_users(database);
    free(database);
}
