/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** parse_client_input.c
*/

#include "../include/server.h"

bool check_doubled_quoted_args(char** split_command)
{
    for (int i = 1; split_command[i] != NULL; i++) {
        int len = strlen(split_command[i]);
        if (split_command[i][0] != '"' || split_command[i][len - 1] != '"') {
            printf("Missing quotes around argument %d: %s\n", i,
            split_command[i]);
            return false;
        }
    }
    return true;
}

bool check_is_login_necessary(clients_t* clients, size_t i)
{
    if (COMMANDS_DATA[i].need_login == true && clients->is_logged == false) {
        printf("You need to be logged in to use this command\n");
        return false;
    }
    return true;
}

void check_function_command_args(clients_t* clients, server_data_t* s, size_t i,
char** split_command, database_t* db)
{
    int nb_args = get_size_word_array(split_command) - 1;

    printf("client logged: %d\n", clients->is_logged);

    for (size_t j = 0; COMMANDS_DATA[i].nb_args[j] != -1; j++) {
        if (COMMANDS_DATA[i].nb_args[j] == nb_args) {
            if (!check_is_login_necessary(clients, i))
                return;
            list_args_t args = {
                .client = clients,
                .server_data = s,
                .split_command = split_command,
                .db = db,
            };
            COMMANDS_DATA[i].function(&args);
            return;
        }
    }
    printf("Invalid number of arguments for command %s\n",
    COMMANDS_DATA[i].name);
}

void parse_client_input(clients_t* clients, server_data_t* s,
char* input_buffer, database_t* db)
{
    char** split_command = split_str(input_buffer, " ");

    if (!split_command) {
        printf("split_command is NULL\n");
        return;
    }
    debug_word_array(split_command);
    if (!check_doubled_quoted_args(split_command)) {
        printf(
            "Invalid arguments => args should be quoted with doubled quotes\n");
        free_word_array(split_command);
        return;
    }
    for (size_t i = 0; i < COMMANDS_DATA_SIZE; i++) {
        if (!strcasecmp(split_command[0], COMMANDS_DATA[i].name)) {
            check_function_command_args(clients, s, i, split_command, db);
            free_word_array(split_command);
            return;
        }
    }
    free_word_array(split_command);
    printf("Command not found\n");
}
