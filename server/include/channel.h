/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** channel.h
*/

#pragma once

typedef struct channel_s {
    char uuid[MAX_UUID_STR_LEN];  // Channel unique identifier
    char name[MAX_NAME_LENGTH];  // Channel name
    char description[MAX_DESCRIPTION_LENGTH];  // Channel description
    user_t* creator;        // Pointer to the creator user
    team_t* team;           // Pointer to the parent team
    user_t* users[10];      // Array of pointers to subscribed users
    size_t nb_users;        // Count of subscribed users
    int users_count;        // Count of subscribed users
} channel_t;
