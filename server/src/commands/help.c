/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** help.c
*/

#include "../../include/server.h"

void help(list_args_t* args)
{
    const char* COMMAND_NAMES =
        "/help\n/login\n/logout\n/users\n/user\n/send\n/messages\n/subscribe\n/"
        "subscribed\n/unsubscribe\n/use\n/create\n/list\n/info\n";

    int size = get_size_word_array(args->split_command);

    if (size == 1) {
        dprintf(args->client->client_socket_fd, "214 %s", COMMAND_NAMES);
        return;
    }
    for (size_t i = 0; i < COMMANDS_DATA_SIZE; i++) {
        if (!strcmp(COMMANDS_DATA[i].name, args->split_command[1])) {
            dprintf(args->client->client_socket_fd, "214 %s : %s",
            COMMANDS_DATA[i].name, COMMANDS_DATA[i].description);
            return;
        }
    }
    dprintf(args->client->client_socket_fd, "214 %s", COMMAND_NAMES);
}
