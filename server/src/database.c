/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** database.c
*/

#include "../include/server.h"

database_t init_database(void)
{
    database_t database = {
        .teams = NULL,
        .channels = NULL,
        .threads = NULL,
        .discussions = NULL,
        .clients = NULL,
    };
    return database;
}
