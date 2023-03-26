/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** channels.c
*/

#include "../../include/server.h"

channel_t* create_channel(database_t* db, create_channel_params_t* param)
{
    channel_t* new_channel = malloc(sizeof(channel_t));

    if (new_channel == NULL) {
        printf("Error: Failed to allocate memory for new channel\n");
        return NULL;
    }

    char *channel_uuid = generate_uuid();
    strncpy(new_channel->uuid, channel_uuid, MAX_UUID_STR_LEN);
    strncpy(new_channel->name, param->name, MAX_NAME_LENGTH);
    strncpy(new_channel->description, param->description,
    MAX_DESCRIPTION_LENGTH);
    strncpy(new_channel->creator_uuid, param->creator_uuid, MAX_UUID_STR_LEN);
    strncpy(new_channel->team_uuid, param->team_uuid, MAX_UUID_STR_LEN);
    new_channel->nb_users = 0;
    new_channel->users_count = 0;
    free(channel_uuid);

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
        printf("Channel creator UUID: %s\n", channel->creator_uuid);
        printf("Channel team UUID: %s\n", channel->team_uuid);
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
        }
        LIST_REMOVE(channel, entries);
        free(channel);
    }
}

bool is_channel_exist(database_t* db, char* team_uuid)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries)
    {
        if (!strcmp(channel->team_uuid, team_uuid))
            return true;
    }

    return false;
}

channel_t* find_channel_by_uuid(database_t* db, char* channel_uuid)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries)
    {
        if (!strcmp(channel->uuid, channel_uuid))
            return channel;
    }

    return NULL;
}

void display_channel_info(database_t* db, char* channel_uuid)
{
    channel_t *channel = find_channel_by_uuid(db, channel_uuid);
    if (channel == NULL) {
        printf("Error: Channel not found\n");
        return;
    }

    // Otherwise, display the channel information
    printf("Channel UUID: %s\n", channel->uuid);
    printf("Channel name: %s\n", channel->name);
    printf("Channel description: %s\n", channel->description);
    printf("Channel creator UUID: %s\n", channel->creator_uuid);
    printf("Channel team UUID: %s\n", channel->team_uuid);
    printf("Channel users: \n");

    for (size_t i = 0; i < channel->nb_users; i++)
        printf("    - %s\n", channel->users[i]);

    printf("\n\n");
}

bool add_user_to_channel(database_t* db, char* channel_uuid, char* user_uuid)
{
    channel_t* channel = find_channel_by_uuid(db, channel_uuid);
    if (channel == NULL) {
        printf("Error: Channel not found\n");
        return false;
    }
    user_t* user = NULL;

    for (size_t i = 0; i < channel->nb_users; i++) {
        if (!strcmp(channel->users[i], user_uuid)) {
            printf("Error: User already in the channel\n");
            return false;
        }
    }

    LIST_FOREACH(user, &(db->users), entries) {
        if (!strcmp(user->uuid, user_uuid))
            break;
    }

    if (user == NULL) {
        printf("Error: User not found\n");
        return false;
    }

    strncpy(channel->users[channel->nb_users], user_uuid, MAX_UUID_STR_LEN);
    channel->nb_users++;

    return true;
}

bool remove_user_from_channel(database_t* db, char* channel_uuid,
char* user_uuid)
{
    channel_t* channel = find_channel_by_uuid(db, channel_uuid);
    if (channel == NULL) {
        printf("Error: Channel not found\n");
        return false;
    }

    bool user_found = false;

    size_t user_index = -1;
    for (size_t i = 0; i < channel->nb_users; i++) {
        if (!strcmp(channel->users[i], user_uuid)) {
            user_index = i;
            user_found = true;
            break;
        }
    }
    if (!user_found) {
        printf("Error: User not in the channel\n");
        return false;
    }

    // Remove the user from the channel by shifting the rest of the user array
    for (size_t i = user_index; i < channel->nb_users - 1; i++) {
        strncpy(channel->users[i], channel->users[i + 1], MAX_UUID_STR_LEN);
    }
    channel->nb_users--;

    return true;
}
