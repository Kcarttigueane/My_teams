/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** login.c
*/

#include "../../include/server.h"

void login(list_args_t* args)
{
    printf("LOGIN\n");
    if (args->client->is_logged) {
        dprintf(args->client->client_socket_fd, "530 Already logged in");
        return;
    }
    char* username = args->split_command[1];

    if (strlen(username) > MAX_NAME_LENGTH) {
        dprintf(args->client->client_socket_fd, "530 Username too long");
        args->client->is_logged = false;
        return;
    }

    if (strlen(username) == 0) {
        dprintf(args->client->client_socket_fd, "530 Username too short");
        args->client->is_logged = false;
        return;
    }

    if (user_exists(args->db->clients, username)) {
        dprintf(args->client->client_socket_fd, "530 Username already exists");
        args->client->is_logged = false;
        return;
    }

    char uuid_str[MAX_UUID_STR_LEN];
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);

    if (!add_user(args->db->clients, uuid_str, username)) {
        dprintf(args->client->client_socket_fd, "530 Failed to add user");
        args->client->is_logged = false;
        return;
    }

    args->client->is_logged = true;
    strncpy(args->client->uuid_user, uuid_str, MAX_UUID_STR_LEN);
    dprintf(args->client->client_socket_fd, "200 %s", uuid_str);
    printf("User %s logged in with uuid %s\n", username, uuid_str);
}
