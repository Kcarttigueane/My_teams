/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user.h
*/

#pragma once

typedef struct user_s {
    char uuid[MAX_UUID_STR_LEN];
    char username[MAX_NAME_LENGTH];
} user_t;
