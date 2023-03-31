/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** subscribe.c
*/

#include "../../include/server.h"

void subscribe(list_args_t* args)
{
    remove_quotes(args->split_command[1]);
    team_t* team = find_team_by_uuid(args->db, args->split_command[1]);
    if (team == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->split_command[1]);
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Team not found");
        return;
    }
    if (add_user_to_team(args->db, args->split_command[1],
        args->client->current_user_uuid) == false) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM,
        "Already subscribed or max nb of users in the team has been reached");
        return;
    }
    if (add_user_to_team_channels(args->db, args->split_command[1],
        args->client->current_user_uuid) == false) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR, "Error");
        return;
    }
    dprintf(args->client->socket_fd, SUBSCRIBE_TO_TEAM,
    SUBSCRIBED_TO_TEAM, args->split_command[1], args->client->current_user_uuid);
    server_event_user_subscribed(team->uuid, args->client->current_user_uuid);
}
