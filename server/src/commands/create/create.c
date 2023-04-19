/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** create.c
*/

#include "../../../include/server.h"

static void handle_create_team(list_args_t* args, int nb_args)
{
    if (!error_handling_create_args(args->client->socket_fd, nb_args)) return;

    char *team_name = args->split_command[1];
    char *team_description = args->split_command[2];

    if (!error_handling_name_and_description(args->client->socket_fd,
    team_name, team_description)) return;

    if (is_team_already_exist(args->db, team_name)) {
        send_error(args->client->socket_fd, ALREADY_EXISTS, "Already Exist");
        return;
    }
    team_t* new_teams = create_team(args->db, team_name, team_description);
    if (!new_teams)
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Team not created");

    team_creation_send_json_resp(args, new_teams);
}

static void handle_create_channel(list_args_t* args, int nb_args)
{
    if (!error_handling_create_args(args->client->socket_fd, nb_args)) return;
    team_t* team = find_team_by_uuid(args->db, args->client->current_team_uuid);

    if (!create_channel_error_handling(args, team))
        return;

    create_channel_params_t params = init_create_channel_params(args);

    if (!error_handling_name_and_description(args->client->socket_fd,
        params.name, params.description)) return;

    channel_t* new_channel = create_channel(args->db, &params);

    if (!new_channel) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR, "Malloc");
    } else {
        team_channel_send_json_resp(args, new_channel, team);
    }
}

static void handle_create_thread(list_args_t* args, int nb_args)
{
    if (!error_handling_create_args(args->client->socket_fd, nb_args)) return;
    team_t* team;
    channel_t* channel;
    if (!validate_team_channel(args, &team, &channel)) return;
    if (is_thread_already_exist(args->db, args->split_command[1]) == true) {
        send_error(args->client->socket_fd, ALREADY_EXISTS,
        "Thread already exist");
        return;
    }
    create_thread_params_t params = init_create_thread_params(args);
    if (!error_handling_name_and_description(args->client->socket_fd,
    params.title, params.message)) return;
    thread_t* new_thread = create_thread(args->db, &params);

    if (!new_thread) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Thread not created");
        return;
    }
    thread_creation_send_json_resp(args, new_thread, team);
}

static void handle_create_reply(list_args_t* args)
{
    team_t* team = NULL;
    channel_t* channel = NULL;
    thread_t* thread = NULL;
    if (!validate_team_channel_thread(args, &team, &channel, &thread)) return;
    if (!is_thread_related_to_channel_to_team(team, channel, thread)) {
        dprintf(args->client->socket_fd, UNKNOWN_THREAD_RESP, UNKNOWN_THREAD,
        args->client->current_thread_uuid);
        return;
    }
    if (strlen(args->split_command[1]) > MAX_BODY_LENGTH) return;
    reply_t* new_reply = add_reply_to_thread(
        args->db, args->client->current_thread_uuid,
        args->split_command[1], args->client->current_user_uuid);
    if (!new_reply) {
        send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
        "Reply not created");
        return;
    }
    reply_creation_send_json_resp(args, new_reply, thread->uuid, team);
}

void create(list_args_t* args)
{
    int nb_args = get_size_word_array(args->split_command);
    switch (args->client->use_args_count) {
        case 0:
            handle_create_team(args, nb_args);
            break;
        case 1:
            handle_create_channel(args, nb_args);
            break;
        case 2:
            handle_create_thread(args, nb_args);
            break;
        case 3:
            (nb_args != 2) ? send_error(args->client->socket_fd, 500, "Error")
            : handle_create_reply(args);
            break;
        default:
            send_error(args->client->socket_fd, 500, "Use /use command first");
            break;
    }
}
