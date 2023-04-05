/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** subscribed.c
*/

#include "../../include/server.h"

static void handle_subscribe_one_arg(list_args_t *args)
{
    char* json_resp =
        list_subscribed_teams(args->db, args->client->current_user_uuid);

    if (json_resp == NULL) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Failed to allocate memory for JSON string");
        return;
    }

    dprintf(args->client->socket_fd, "%s", json_resp);
    free(json_resp);
}


static void list_users_of_team(list_args_t* args, char* team_uuid)
{
    if (strlen(team_uuid) != (MAX_UUID_LENGTH - 1)) {
        send_error(args->client->socket_fd, UNKNOWN_TEAM, "Invalid UUID");
        return;
    }
    team_t* team = find_team_by_uuid(args->db, team_uuid);

    if (!team) {
        dprintf(args->client->socket_fd, UNKNOWN_TEAM_RESP, UNKNOWN_TEAM,
        team_uuid);
        return;
    }

    char *json_resp = list_users_subscribed_to_team(args->db, team);
    if (json_resp == NULL) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Failed to allocate memory for JSON string");
        return;
    }
    dprintf(args->client->socket_fd, "%s", json_resp);
}

void subscribed(list_args_t* args)
{
    size_t size = get_size_word_array(args->split_command) - 1;

    if (size == 0) {
        handle_subscribe_one_arg(args);
    } else if (size == 1) {
        list_users_of_team(args, args->split_command[1]);
    }
}
