/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** info.c
*/

#include "../../../include/server.h"

void info(__attribute_maybe_unused__ list_args_t* args)
{
    printf("INFO\n");

    if (args->client->use_args_count == FAILURE) {
        dprintf(args->client->socket_fd, "530 User the endpoint /use first\n");
        return;
    }

    if (args->client->use_args_count == 0) {
        user_t* user =
            find_user_by_uuid(args->db, args->client->current_user_uuid);

        if (user == NULL) {
            dprintf(args->client->socket_fd, "530 User not found");
            return;
        }
    }
    if (args->client->use_args_count == 1) {
        display_team_info(args->db, args->split_command[1]);
    }
    if (args->client->use_args_count == 2) {
        display_channel_info(args->db, args->split_command[2]);
    }
    if (args->client->use_args_count == 3) {
        // display_thread_info(args->db, args->split_command[3]);
    }
}
