/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** unsubscribe.c
*/

#include "../../include/server.h"

void unsubscribe(list_args_t* args)
{
    team_t* team = find_team_by_uuid(args->db, args->split_command[1]);
    if (team == NULL) {
        send_error(args->client->socket_fd, UNAUTHORIZED, "Team not found");
        return;
    }
    if (remove_user_from_team(args->db, args->split_command[1],
        args->client->current_user_uuid) == false) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM,
        "User not found in the team");
        return;
    }
    if (remove_user_from_team_channels(args->db, args->split_command[1],
        args->client->current_user_uuid) == false) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "User not found in the team");
        return;
    }
    dprintf(args->client->socket_fd, UNSUBSCRIBE_TO_TEAM, SUBSCRIBED_TO_TEAM,
    args->split_command[1]);
}
