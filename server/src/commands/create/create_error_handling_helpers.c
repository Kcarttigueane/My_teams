/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_error_handling_helpers.c
*/

#include "../../../include/server.h"

bool create_channel_error_handling(list_args_t* args, team_t* team)
{
    if (!team) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        args->client->current_team_uuid);
        return false;
    }
    if (!is_user_in_team(team, args->client->current_user_uuid)) {
        send_error(args->client->socket_fd, UNAUTHORIZED,
        "Not a menber of the team");
        return false;
    }
    if (is_channel_already_exist(args->db, args->split_command[1])) {
        send_error(args->client->socket_fd, ALREADY_EXISTS,
        "Channel already exist");
        return false;
    }
    return true;
}
