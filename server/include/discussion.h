/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** discussion.h
*/

#pragma once

typedef struct discussion_s {
    char uuid[MAX_UUID_STR_LEN];  // Discussion unique identifier
    user_t* sender;              // Pointer to the sender user
    user_t* receiver;            // Pointer to the receiver user
    message_t* messages;         // Pointer to the linked list of messages
    LIST_ENTRY(discussion_s) entries;  // Pointer to the next discussion in the linked list
} discussion_t;
