/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** channels.c
*/

#include "../../include/server.h"

channel_t* create_channel(database_t* db, char* name, char* description,
user_t* creator, team_t* team)
{
    channel_t* new_channel = malloc(sizeof(channel_t));

    if (new_channel == NULL) {
        printf("Error: Failed to allocate memory for new channel\n");
        return NULL;
    }

    strncpy(new_channel->uuid, generate_uuid(), MAX_UUID_STR_LEN);
    strncpy(new_channel->name, name, MAX_NAME_LENGTH);
    strncpy(new_channel->description, description, MAX_DESCRIPTION_LENGTH);
    new_channel->creator = creator;
    new_channel->team = team;
    new_channel->nb_users = 0;
    new_channel->users_count = 0;

    LIST_INSERT_HEAD(&(db->channels), new_channel, entries);

    return new_channel;
}

void list_channels(database_t* db)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries)
    {
        printf("Channel UUID: %s\n", channel->uuid);
        printf("Channel name: %s\n", channel->name);
        printf("Channel description: %s\n", channel->description);
        printf("Channel creator UUID: %s\n", channel->creator->uuid);
        printf("Channel team UUID: %s\n", channel->team->uuid);
        printf("Channel users: ");

        for (size_t i = 0; i < channel->nb_users; i++)
            printf("%s ", channel->users[i]);

        printf("\n\n");
    }
}

void free_channels(database_t* db)
{
    channel_t* channel;

    while ((channel = LIST_FIRST(&(db->channels))) != NULL) {
        while (channel->nb_users > 0) {
            channel->nb_users--;
            // channel->users[channel->nb_users] = NULL;
        }
        LIST_REMOVE(channel, entries);
        free(channel);
    }
}

bool is_channel_exist(database_t* db, char* team_uuid)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries) {
        if (!strcmp(channel->team->uuid, team_uuid))
            return true;
    }

    return false;
}

void display_channel_info(database_t* db, char* channel_uuid)
{
    channel_t* channel = NULL;

    // Search for the channel with the specified UUID
    LIST_FOREACH(channel, &(db->channels), entries)
    {
        if (!strcmp(channel->uuid, channel_uuid))
            break;
    }

    // If the channel was not found, display an error message and return
    if (channel == NULL) {
        printf("Error: Channel not found\n");
        return;
    }

    // Otherwise, display the channel information
    printf("Channel UUID: %s\n", channel->uuid);
    printf("Channel name: %s\n", channel->name);
    printf("Channel description: %s\n", channel->description);
    printf("Channel creator UUID: %s\n", channel->creator->uuid);
    printf("Channel team UUID: %s\n", channel->team->uuid);
    printf("Channel users: ");

    for (size_t i = 0; i < channel->nb_users; i++)
        printf("%s ", channel->users[i]);

    printf("\n\n");
}
