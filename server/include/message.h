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
    char sender_uuid[MAX_UUID_STR_LEN];
    LIST_ENTRY(message_s) entries;
} message_t;
