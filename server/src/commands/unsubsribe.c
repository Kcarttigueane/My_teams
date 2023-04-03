/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** unsubscribe.c
*/

#include "../../include/server.h"

static bool handle_team_unsubscription(database_t* db, char* team_uuid,
char* user_uuid)
{
    if (!remove_user_from_team(db, team_uuid, user_uuid))
        return false;

    if (!remove_user_from_team_channels(db, team_uuid, user_uuid))
        return false;

    return true;
}

void unsubscribe(list_args_t* args)
{
    char* team_uuid = args->split_command[1];
    if (strlen(team_uuid) != (MAX_UUID_LENGTH - 1)) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Invalid UUID");
        return;
    }
    team_t* team = find_team_by_uuid(args->db, team_uuid);
    if (team == NULL) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        team_uuid);
        return;
    }
    char* user_uuid = args->client->current_user_uuid;
    if (!handle_team_unsubscription(args->db, team_uuid, user_uuid)) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM,
        "User not found in the team");
        return;
    }
    dprintf(args->client->socket_fd, UNSUBSCRIBE_TO_TEAM, SUBSCRIBED_TO_TEAM,
    team_uuid, user_uuid);
    server_event_user_unsubscribed(team->uuid, user_uuid);
}
