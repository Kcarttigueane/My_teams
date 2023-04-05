/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** is_channel_list_empty.c
*/

#include "../../../include/server.h"

bool is_channel_list_empty(database_t* db)
{
    return (LIST_EMPTY(&db->channels)) ? false : true;
}
