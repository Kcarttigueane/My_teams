/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** thread.h
*/

#pragma once

typedef struct thread_s {
    char uuid[MAX_UUID_STR_LEN];  // Thread unique identifier
    char title[MAX_NAME_LENGTH];  // Thread title
    char message[MAX_BODY_LENGTH];  // Thread message
    channel_t* channel;          // Pointer to the parent channel
    user_t* creator;             // Pointer to the creator user
    user_t* user;                // Pointer to the user who created the thread
    struct comment_s* comments;  // Pointer to the linked list of comments
} thread_t;
