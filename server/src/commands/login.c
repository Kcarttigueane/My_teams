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

    // if (user_exists(args->db->clients, username)) {
    //     dprintf(args->client->client_socket_fd, "530 Username already exists");
    //     args->client->is_logged = false;
    //     return;
    // }
    //  ! SHOULD CHECK IF THE USERNAME HAS THE LENGTH OF 32 BEFORE

    user_t *user = create_user(args->db, generate_uuid(), username);

    if (user == NULL) {
        dprintf(args->client->client_socket_fd, "530 Failed to create user");
        args->client->is_logged = false;
        return;
    }

    args->client->is_logged = true;
    strncpy(args->client->current_user_uuid, user->uuid, MAX_UUID_STR_LEN);
    dprintf(args->client->client_socket_fd, "200 %s", user->uuid);
    printf("User %s logged in with uuid %s\n", username, user->uuid);
}
