/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** handle_server_inputs.c
*/

#include "../include/client.h"
#include "../include/color.h"

int handle_server_input(client_data_t* client, char* buffer)
{
    ssize_t bytes_received = recv(client->socket_fd, buffer, BUFFER_SIZE, 0);

    if (bytes_received <= 0) {
        exit_with_error("Server closed connection.\n");
    }
    printf(RED);
    printf("---------------Received from server:----------------\n");
    printf(YELLOW);
    printf("%s\n", buffer);
    printf(RED);
    printf("-----------End of received from server:-----------\n");
    printf(RESET);
    printf(CYAN);
    printf("%s", CLIENT_PROMPT);
    printf(RESET);
    fflush(stdout);

    return SUCCESS;
}
