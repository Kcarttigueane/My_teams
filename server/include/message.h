/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** message.h
*/

#pragma once

typedef struct message_s {
    char uuid[MAX_UUID_STR_LEN];
    char body[MAX_BODY_LENGTH];
    user_t* sender;
    LIST_ENTRY(message_s) entries;
} message_t;
