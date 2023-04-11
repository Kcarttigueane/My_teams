/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** parse_client_input.c
*/

#include "../include/server.h"

void check_command_args(list_args_t* args, size_t cmd_index)
{
    int nb_args = get_size_word_array(args->split_command) - 1;

    bool login_required = is_login_required(args->client, cmd_index);

    if (login_required) {
        send_error(args->client->socket_fd, UNAUTHORIZED,
        "You need to be logged in");
        return;
    }

    for (size_t j = 0; COMMANDS_DATA[cmd_index].nb_args[j] != -1; j++) {
        if (COMMANDS_DATA[cmd_index].nb_args[j] == nb_args) {
            COMMANDS_DATA[cmd_index].function(args);
            return;
        }
    }
    send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
    "Invalid number of arguments");
}

void parse_client_input(list_args_t* args, char* input_buffer)
{
    char** split_command = split_str(input_buffer, "\n");

    if (!handle_input_error(split_command)) return;

    for (size_t i = 0; i < COMMANDS_DATA_SIZE; i++) {
        if (!strcasecmp(split_command[0], COMMANDS_DATA[i].name)) {
            args->split_command = split_command;
            check_command_args(args, i);
            free_word_array(split_command);
            return;
        }
    }
    free_word_array(split_command);

    send_error(args->client->socket_fd, INTERNAL_SERVER_ERROR,
    "Invalid command");
}
