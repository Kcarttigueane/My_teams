/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_team_channel_helper.c
*/

#include "../../../include/server.h"

static void notify_team_members(list_args_t* args, channel_t* new_channel,
team_t* team)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (args->clients[i].socket_fd == 0)
            continue;
        for (size_t j = 0; j < 10; j++) {
            (args->clients[i].is_logged &&
            !strcmp(args->clients[i].current_user_uuid, team->users[j])) ?
                dprintf(args->clients[i].socket_fd, CREATE_CHANNEL_RESP,
                CHANNEL_CREATED, new_channel->uuid,
                new_channel->name, new_channel->description) :
                (void)0;
        }
    }
}

void team_channel_send_json_resp(list_args_t* args, channel_t* new_channel,
team_t* team)
{
    server_event_channel_created(new_channel->team_uuid, new_channel->uuid,
    new_channel->name);

    dprintf(args->client->socket_fd, CREATE_CHANNEL_RESP,
    CHANNEL_CREATED_NOTIFICATION, new_channel->uuid, new_channel->name,
    new_channel->description);

    notify_team_members(args, new_channel, team);
}
