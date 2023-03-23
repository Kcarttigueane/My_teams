/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** parse_client_input.c
*/

#include "../include/server.h"

void check_function_command_args(clients_t clients, server_data_t* s, size_t i,
char** split_command)
{
    int nb_args = get_size_word_array(split_command);

    for (size_t j = 0; COMMANDS_DATA[i].nb_args[j] < -1; i++) {
        if (COMMANDS_DATA[i].nb_args[j] == nb_args) {
            list_args_t args = {
                .client = &clients,
                .server_data = s,
                .split_command = split_command,
            };
            COMMANDS_DATA[i].function(&args);
            free_word_array(split_command);
        }
    }
    printf("Invalid number of arguments for command %s\n",
    COMMANDS_DATA[i].name);
}

void parse_client_input(clients_t clients, server_data_t* s, char* input_buffer)
{
    printf("input_buffer: %s\n", input_buffer);
    char** split_command = split_str(input_buffer, " ");

    if (!split_command) {
        printf("split_command is NULL\n");
        return;
    }
    debug_word_array(split_command);

    for (size_t i = 0; i < COMMANDS_DATA_SIZE; i++) {
        if (!strcasecmp(split_command[0], COMMANDS_DATA[i].name)) {
            check_function_command_args(clients, s, i, split_command);
            return;
        }
    }
    free_word_array(split_command);
    printf("Command not found\n");
}
