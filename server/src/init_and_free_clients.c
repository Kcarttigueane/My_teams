/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** init_and_free_clients.c
*/

#include "../include/server.h"

void initialize_clients(clients_t* clients)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++)
        clients[i].use_args_count = FAILURE;
}

void free_clients(clients_t* clients)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].socket_fd > 0)
            close(clients[i].socket_fd);
    }
    free(clients);
}
