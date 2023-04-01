/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** message.h
*/

#pragma once

typedef struct message_s {
    char uuid[MAX_UUID_LENGTH];
    char body[MAX_BODY_LENGTH];
    char sender_uuid[MAX_UUID_LENGTH];
    time_t created_at;
    LIST_ENTRY(message_s) entries;
} message_t;
