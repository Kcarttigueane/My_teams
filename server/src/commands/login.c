/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** login.c
*/

#include "../../include/server.h"

static bool error_handling_login(list_args_t* args, char* username)
{
    if (args->client->is_logged) {
        send_error(args->client->socket_fd, CONNECTION_DENIED,
        "Already logged in");
        return false;
    }

    if (strlen(username) > MAX_NAME_LENGTH) {
        send_error(args->client->socket_fd, CONNECTION_DENIED,
        "Username too long");
        args->client->is_logged = false;
        return false;
    }

    if (strlen(username) == 0) {
        send_error(args->client->socket_fd, CONNECTION_DENIED,
        "Username too short");
        args->client->is_logged = false;
        return false;
    }
    return true;
}

static void notify_all_users_of_login(list_args_t* args, user_t* user)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (args->clients[i].socket_fd == 0)
            continue;
        if (args->clients[i].is_logged)
            dprintf(args->clients[i].socket_fd, LOGIN_JSON_RESP,
            CONNECTION_SUCCESSFUL, user->username, user->uuid);
    }
}

void create_and_log_user(list_args_t* args, char* username)
{
    user_t* user = create_user(args->db, username);

    if (!user) {
        send_error(args->client->socket_fd, CONNECTION_DENIED,
        "Failed to create user");
        args->client->is_logged = false;
        return;
    }

    server_event_user_created(user->uuid, user->username);

    args->client->is_logged = true;
    strncpy(args->client->current_user_uuid, user->uuid, MAX_UUID_LENGTH);
    user->is_logged_in = true;

    server_event_user_logged_in(user->uuid);

    notify_all_users_of_login(args, user);
}

void login(list_args_t* args)
{
    char* username = args->split_command[1];

    if (!error_handling_login(args, username))
        return;

    user_t* user = NULL;

    if ((user = find_user_by_username(args->db, username)) != NULL) {
        args->client->is_logged = true;
        strncpy(args->client->current_user_uuid, user->uuid, MAX_UUID_LENGTH);
        user->is_logged_in = true;
        server_event_user_logged_in(user->uuid);
        notify_all_users_of_login(args, user);
        return;
    }

    create_and_log_user(args, username);
}
