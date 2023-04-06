/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_utils.c
*/

#include "../../../include/server.h"

create_channel_params_t init_create_channel_params(list_args_t* args)
{
    create_channel_params_t params = {0};

    strcpy(params.name, args->split_command[1]);
    strcpy(params.description, args->split_command[2]);
    strcpy(params.team_uuid, args->client->current_team_uuid);
    strcpy(params.creator_uuid, args->client->current_user_uuid);

    return params;
}

create_thread_params_t init_create_thread_params(list_args_t* args)
{
    create_thread_params_t params = {0};

    strcpy(params.title, args->split_command[1]);
    strcpy(params.message, args->split_command[2]);
    strcpy(params.related_channel_uuid, args->client->current_channel_uuid);
    strcpy(params.creator_uuid, args->client->current_user_uuid);

    return params;
}

bool error_handling_create_args(int socket_fd, int nb_args)
{
    if (nb_args != 3) {
        send_error(socket_fd, INTERNAL_SERVER_ERROR, "Wrong number of args");
        return false;
    }
    return true;
}
