/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** subscribed.c
*/

#include "../../include/server.h"

void subscribed(list_args_t* args)
{
    size_t size = get_size_word_array(args->split_command) - 1;

    if (size == 0) {
        list_subscribed_teams(args->db, args->client->current_user_uuid);
    } else if (size == 1) {
        list_users_subscribed_to_team(args->db, args->split_command[1]);
    }
}
