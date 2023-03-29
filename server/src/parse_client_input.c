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
        printf("You need to be logged in to use this command\n");
        return;
    }

    for (size_t j = 0; COMMANDS_DATA[cmd_index].nb_args[j] != -1; j++) {
        if (COMMANDS_DATA[cmd_index].nb_args[j] == nb_args) {
            COMMANDS_DATA[cmd_index].function(args);
            return;
        }
    }

    printf("Invalid number of arguments for command %s\n",
    COMMANDS_DATA[cmd_index].name);
}

void parse_client_input(clients_t* clients, server_data_t* s,
char* input_buffer, database_t* db)
{
    char** split_command = split_str(input_buffer, " ");

    if (!handle_input_error(split_command))
        return;

    for (size_t i = 0; i < COMMANDS_DATA_SIZE; i++) {
        if (!strcasecmp(split_command[0], COMMANDS_DATA[i].name)) {
            list_args_t args = {
                .client = clients,
                .server_data = s,
                .split_command = split_command,
                .db = db,
            };
            check_command_args(&args, i);
            free_word_array(split_command);
            return;
        }
    }
    free_word_array(split_command);
    send_error(clients->socket_fd, 500, "Invalid command");
}
