/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_channel.c
*/

#include "../../../include/server.h"

static channel_t* create_channel_obj(create_channel_params_t* param)
{
    channel_t* new_channel = (channel_t*)malloc(sizeof(channel_t));

    if (new_channel == NULL) {
        printf("Error: Failed to allocate memory for new channel\n");
        return NULL;
    }
    char* channel_uuid = generate_uuid();

    strncpy(new_channel->uuid, channel_uuid, MAX_UUID_LENGTH);
    strncpy(new_channel->name, param->name, MAX_NAME_LENGTH);
    strncpy(new_channel->description, param->description,
    MAX_DESCRIPTION_LENGTH);
    strncpy(new_channel->creator_uuid, param->creator_uuid, MAX_UUID_LENGTH);
    strncpy(new_channel->team_uuid, param->team_uuid, MAX_UUID_LENGTH);
    new_channel->nb_users = 0;
    new_channel->created_at = time(NULL);

    free(channel_uuid);
    return new_channel;
}

channel_t* create_channel(database_t* db, create_channel_params_t* param)
{
    channel_t* new_channel = create_channel_obj(param);

    if (new_channel == NULL)
        return NULL;

    LIST_INSERT_HEAD(&(db->channels), new_channel, entries);

    return new_channel;
}
