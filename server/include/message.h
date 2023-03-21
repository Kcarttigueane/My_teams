/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** message.h
*/

#pragma once

typedef struct message_s {
    char uuid[MAX_UUID_STR_LEN];  // Message unique identifier
    char body[MAX_BODY_LENGTH];  // Message body
    user_t* sender;          // Pointer to the sender user
    struct message_s* next;  // Pointer to the next message in the linked list
} message_t;
