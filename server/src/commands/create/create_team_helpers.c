/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_team_helpers.c
*/

#include "../../../include/server.h"

static void notify_team_members(list_args_t* args, team_t* new_team)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (args->clients[i].socket_fd == 0)
            continue;
        if (args->clients[i].is_logged)
            dprintf(args->clients[i].socket_fd, CREATE_TEAM_RESP, TEAM_CREATED,
            new_team->uuid, new_team->name, new_team->description);
    }
}

void team_creation_send_json_resp(list_args_t* args, team_t* new_team)
{
    server_event_team_created(new_team->uuid, new_team->name,
    args->client->current_user_uuid);

    dprintf(args->client->socket_fd, CREATE_TEAM_RESP,
    TEAM_CREATED_NOTIFICATION, new_team->uuid, new_team->name,
    new_team->description);

    notify_team_members(args, new_team);
}
