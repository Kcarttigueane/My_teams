/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** handle_input_error.c
*/

#include "../include/server.h"

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
    return true;
}
