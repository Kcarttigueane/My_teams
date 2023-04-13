/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** subscribe.c
*/

#include "../../include/server.h"

static bool handle_team_not_found(list_args_t* args, team_t* team,
char* team_uuid)
{
    if (!team) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        team_uuid);
        return true;
    }
    return false;
}

static bool handle_user_not_added_to_team(list_args_t* args, char* team_uuid)
{
    if (!add_user_to_team(args->db, team_uuid,
        args->client->current_user_uuid)) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        team_uuid);
        send_error(args->client->socket_fd, UNKNOWN_TEAM,
        "Already subscribed or max nb of users in the team has been "
        "reached");
        return true;
    }
    return false;
}

void subscribe(list_args_t* args)
{
    char* team_uuid = args->split_command[1];

    if (strlen(team_uuid) != (MAX_UUID_LENGTH - 1)) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Invalid UUID");
        return;
    }

    team_t* team = find_team_by_uuid(args->db, team_uuid);

    if (handle_team_not_found(args, team, team_uuid))
        return;
    if (handle_user_not_added_to_team(args, team_uuid))
        return;

    dprintf(args->client->socket_fd, SUBSCRIBE_TO_TEAM, SUBSCRIBED_TO_TEAM,
    team_uuid, args->client->current_user_uuid);

    server_event_user_subscribed(team->uuid, args->client->current_user_uuid);
}
