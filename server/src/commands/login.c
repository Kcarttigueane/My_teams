/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** login.c
*/

#include "../../include/server.h"

bool error_handling_login(list_args_t* args, char* username)
{
    if (args->client->is_logged) {
        send_json_error_response(args->client->client_socket_fd,
        CONNECTION_DENIED, "Already logged in");
        return false;
    }

    if (strlen(username) > MAX_NAME_LENGTH) {
        send_json_error_response(args->client->client_socket_fd,
        CONNECTION_DENIED, "Username too long");
        args->client->is_logged = false;
        return false;
    }

    if (strlen(username) == 0) {
        send_json_error_response(args->client->client_socket_fd,
        CONNECTION_DENIED, "Username too short");
        args->client->is_logged = false;
        return false;
    }
    return true;
}

void login(list_args_t* args)
{
    char* username = args->split_command[1];

    if (!error_handling_login(args, username)) return;

    user_t* user = NULL;

    if ((user = find_user_by_username(args->db, username)) != NULL) {
        args->client->is_logged = true;
        strncpy(args->client->current_user_uuid, user->uuid, MAX_UUID_STR_LEN);
        // ** server_event_user_logged_in(char const* user_uuid); // ! LOGGING LIB
        return;
    }

    user = create_user(args->db, username);

    if (user == NULL) {
        send_json_error_response(args->client->client_socket_fd,
        CONNECTION_DENIED, "Failed to create user");
        args->client->is_logged = false;
        return;
    }

    args->client->is_logged = true;
    strncpy(args->client->current_user_uuid, user->uuid, MAX_UUID_STR_LEN);

    // ** server_event_user_logged_in(char const* user_uuid); // ! LOGGING LIB

    dprintf(args->client->client_socket_fd, LOGIN_JSON_REP, user->username,
    user->uuid);
    printf("User %s logged in with uuid %s\n", username, user->uuid);
}
