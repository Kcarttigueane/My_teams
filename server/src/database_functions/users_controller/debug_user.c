/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** debug_user.c
*/

#include "../../../include/server.h"
#include "../../../../include/color.h"

void debug_user(user_t* user)
{
    printf(GREEN);
    printf("[User created]\t");
    printf(BLUE);
    printf(" [UUID] %s\t", user->uuid);
    printf(CYAN);
    printf(" [Username] %s\n", user->username);
    printf(" [IS_LOGGED_IN] %d\t", user->is_logged_in);
    printf(RESET);
}
