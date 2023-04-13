/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** logout.c
*/

#include "../../include/server.h"

static void notify_all_users_of_logout(list_args_t* args, user_t* user)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (args->clients[i].socket_fd == 0)
            continue;
        if (args->clients[i].is_logged)
            dprintf(args->clients[i].socket_fd, LOGOUT_JSON_RESP,
                CONNECTION_SUCCESSFUL, user->username, user->uuid);
    }
}

void logout(list_args_t* args)
{
    user_t* user = find_user_by_uuid(args->db, args->client->current_user_uuid);

    if (!user)
        send_error(args->client->socket_fd, UNKNOWN_USER, "Unknown user");

    args->client->current_user_uuid[0] = '\0';
    args->client->is_logged = false;
    user->is_logged_in = false;

    server_event_user_logged_out(user->uuid);

    notify_all_users_of_logout(args, user);

    close(args->client->socket_fd);

    args->client->socket_fd = 0;
}
