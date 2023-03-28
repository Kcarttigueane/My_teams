/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** handle_input_error.c
*/

#include "../include/server.h"

bool is_quoted_arg(const char* arg)
{
    int len = strlen(arg);
    return (len >= 2 && arg[0] == '"' && arg[len - 1] == '"');
}

bool check_quoted_args(char** args)
{
    for (int i = 1; args[i] != NULL; i++) {
        if (!is_quoted_arg(args[i])) {
            printf("Missing quotes around argument %d: %s\n", i, args[i]);
            return false;
        }
    }
    return true;
}

bool is_login_required(const clients_t* client, size_t cmd_index)
{
    return (COMMANDS_DATA[cmd_index].need_login && !client->is_logged);
}

bool handle_input_error(char** split_command)
{
    if (!split_command) {
        printf("split_command is NULL\n");
        return false;
    }
    debug_word_array(split_command);
    if (!check_quoted_args(split_command)) {
        printf(
            "Invalid arguments => args should be quoted with doubled quotes\n");
        free_word_array(split_command);
        return false;
    }
    return true;
}
