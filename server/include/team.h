/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** team.h
*/

#pragma once

typedef struct team_s {
    char uuid[MAX_UUID_STR_LEN];  // Team unique identifier
    char name[MAX_NAME_LENGTH];  // Team name
    char description[MAX_DESCRIPTION_LENGTH];  // Team description
    user_t* users[10];      // Array of pointers to subscribed users
    int users_count;        // Count of subscribed users
} team_t;
