/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_channel.c
*/

#include "../../../include/server.h"

void list_channels(database_t* db)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries) {
        printf("Channel UUID: %s\n", channel->uuid);
        printf("Channel name: %s\n", channel->name);
        printf("Channel description: %s\n", channel->description);
        printf("Channel creator UUID: %s\n", channel->creator_uuid);
        printf("Channel team UUID: %s\n", channel->team_uuid);
        printf("Current Unix timestamp: %ld\n", (long)channel->created_at);
        printf("Channel users: ");

        for (size_t i = 0; i < channel->nb_users; i++)
            printf("%s ", channel->users[i]);

        printf("\n\n");
    }
}

void display_channel_info(database_t* db, char* channel_uuid)
{
    channel_t* channel = find_channel_by_uuid(db, channel_uuid);
    if (channel == NULL) {
        printf("Error: Channel not found\n");
        return;
    }

    printf("Channel UUID: %s\n", channel->uuid);
    printf("Channel name: %s\n", channel->name);
    printf("Channel description: %s\n", channel->description);
    printf("Channel creator UUID: %s\n", channel->creator_uuid);
    printf("Channel team UUID: %s\n", channel->team_uuid);
    printf("Current Unix timestamp: %ld\n", (long)channel->created_at);
    printf("Channel users: \n");

    for (size_t i = 0; i < channel->nb_users; i++)
        printf("    - %s\n", channel->users[i]);

    printf("\n\n");
}
