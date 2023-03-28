/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** create.c
*/

#include "../../../include/server.h"

void create(__attribute_maybe_unused__ list_args_t* args)
{
    printf("CREATE\n");

    printf("/user -> nb args: %d\n", args->client->use_args_count);

    if (args->client->use_args_count == 0) {
        team_t* new_teams = create_team(args->db, args->split_command[1],
                                        args->split_command[2]);
        dprintf(args->client->socket_fd, CREATE_TEAM, new_teams->uuid,
                new_teams->name, new_teams->description);
        return;
    }

    if (args->client->use_args_count == 1) {
        create_channel_params_t params = {0};

        strcpy(params.name, args->split_command[1]);
        strcpy(params.description, args->split_command[2]);
        strcpy(params.team_uuid, args->client->current_team_uuid);
        strcpy(params.creator_uuid, args->client->current_user_uuid);

        channel_t* new_channel = create_channel(args->db, &params);

        if (new_channel == NULL) {
            send_json_error_response(args->client->socket_fd, 530,
                                     "Channel not created");
        }

        dprintf(args->client->socket_fd, CREATE_CHANNEL,
                new_channel->uuid, new_channel->name, new_channel->description);

        return;
    }

    if (args->client->use_args_count == 2) {
        create_thread_params_t params = {0};

        strcpy(params.title, args->split_command[1]);
        strcpy(params.message, args->split_command[2]);
        strcpy(params.related_channel_uuid, args->client->current_channel_uuid);
        strcpy(params.creator_uuid, args->client->current_user_uuid);

        thread_t* new_thread = create_thread(args->db, &params);
        if (new_thread == NULL) {
            send_json_error_response(args->client->socket_fd, 530,
                                     "Thread not created");
        }

        dprintf(args->client->socket_fd, CREATE_THREAD, new_thread->uuid,
                new_thread->title, new_thread->message,
                (long)new_thread->created_at);

        return;
    }

    if (args->client->use_args_count == 3) {
        reply_t* new_reply = add_reply_to_thread(
            args->db, args->client->current_team_uuid, args->split_command[1],
            args->client->current_user_uuid);

        if (new_reply == NULL) {
            send_json_error_response(args->client->socket_fd, 530,
                                     "Reply not created");
            return;
        }

        dprintf(args->client->socket_fd, CREATE_REPLY, new_reply->uuid,
                new_reply->body, (long)new_reply->created_at);

        return;
    }
}
