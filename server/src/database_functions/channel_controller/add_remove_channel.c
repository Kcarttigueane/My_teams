/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** add_remove_channel.c
*/

#include "../../../include/server.h"

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
