/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** add_remove_channel.c
*/

#include "../../../include/server.h"

static ssize_t find_user_in_channel(channel_t* channel, const char* user_uuid)
{
    for (size_t i = 0; i < channel->nb_users; i++) {
        if (!strcmp(channel->users[i], user_uuid)) {
            return (ssize_t)i;
        }
    }
    return FAILURE;
}

bool add_user_to_channel(database_t* db, char* channel_uuid, char* user_uuid)
{
    channel_t* channel = find_channel_by_uuid(db, channel_uuid);
    if (!channel)
        return false;

    ssize_t user_index = find_user_in_channel(channel, user_uuid);
    if (user_index >= 0) {
        printf("Error: User already in the channel\n");
        return false;
    }

    user_t* user = find_user_by_uuid(db, user_uuid);
    if (!user)
        return false;

    strncpy(channel->users[channel->nb_users], user_uuid, MAX_UUID_STR_LEN);
    channel->nb_users++;

    return true;
}

bool remove_user_from_channel(database_t* db, char* channel_uuid,
char* user_uuid)
{
    channel_t* channel = find_channel_by_uuid(db, channel_uuid);
    if (!channel)
        return false;

    ssize_t user_index = find_user_in_channel(channel, user_uuid);
    if (user_index < 0) {
        printf("Error: User not in the channel\n");
        return false;
    }

    for (size_t i = user_index; i < channel->nb_users - 1; i++) {
        strncpy(channel->users[i], channel->users[i + 1], MAX_UUID_STR_LEN);
    }
    channel->nb_users--;

    return true;
}
