/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** are_users_exist.c
*/

#include "../../../include/server.h"

bool is_users_list_empty(database_t* db)
{
    if (LIST_EMPTY(&db->users))
        return true;
    return false;
}
