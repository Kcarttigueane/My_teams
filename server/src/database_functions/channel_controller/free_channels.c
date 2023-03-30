/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** free_channels.c
*/

#include "../../../include/server.h"

void free_channels(database_t* db)
{
    channel_t* channel;

    while ((channel = LIST_FIRST(&(db->channels))) != NULL) {
        while (channel->nb_users > 0) {
            channel->nb_users--;
        }
        LIST_REMOVE(channel, entries);
        free(channel);
    }
}
