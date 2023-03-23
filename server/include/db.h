/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** db.h
*/

#pragma once

typedef struct database {
    team_t* teams;
    channel_t* channels;
    thread_t* threads;
    discussion_t* discussions;
    clients_t* clients;
} database_t;
