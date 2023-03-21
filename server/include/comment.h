/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** comment.h
*/

#pragma once

typedef struct comment_s {
    char uuid[MAX_UUID_STR_LEN];  // Comment unique identifier
    char body[MAX_BODY_LENGTH];  // Comment body
    user_t* user;            // Pointer to the user who created the comment
    struct comment_s* next;  // Pointer to the next comment in the linked list
} comment_t;
