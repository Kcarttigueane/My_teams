/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** find_client_by_uuid.c
*/

#include "../include/server.h"

clients_t* find_client_by_uuid(clients_t* clients, char* uuid)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_logged && !strcmp(clients[i].current_user_uuid, uuid))
            return &clients[i];
    }
    return NULL;
}
