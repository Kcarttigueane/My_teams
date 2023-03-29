/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** unsubscribe.c
*/

#include "../../include/server.h"

void unsubscribe(__attribute_maybe_unused__ list_args_t* args)
{
    printf("UNSUBSCRIBE\n");
    team_t* team = find_team_by_uuid(args->db, args->split_command[1]);
    if (team == NULL) {
        send_error(args->client->socket_fd, 404, "Team not found");
        return;
    }
    if (remove_user_from_team(args->db, args->split_command[1],
        args->client->current_user_uuid) == false) {
        send_error(args->client->socket_fd, 400,
        "User not found in the team");
        return;
    }
    if (remove_user_from_team_channels(args->db, args->split_command[1],
        args->client->current_user_uuid) == false) {
        send_error(args->client->socket_fd, 400,
        "User not found in the team");
        return;
    }
    dprintf(args->client->socket_fd, UNSUBSCRIBE_TO_TEAM,
    args->split_command[1]);
}
