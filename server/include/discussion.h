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
    struct message_s* messages;  // Pointer to the linked list of messages
} discussion_t;
