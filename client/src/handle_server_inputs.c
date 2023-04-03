/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** handle_server_inputs.c
*/

#include "../include/client.h"
#include "../include/color.h"

static void analyze_server_response(char* buffer)
{
    int status_code = get_status_code(buffer);

    for (size_t i = 0; i < LIST_EVENTS_CODE_SIZE; i++) {
        if (status_code == LIST_EVENTS_CODE[i].status_code) {
            LIST_EVENTS_CODE[i].function(buffer);
            break;
        }
    }
}

int handle_server_input(client_data_t* client, char* buffer)
{
    ssize_t bytes_received = recv(client->socket_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0)
        exit_with_error("Server closed connection.\n");

    printf(RED);
    printf("---------------Received from server:----------------\n");
    printf(YELLOW);
    printf("%s\n", buffer);
    printf(RED);
    printf("-----------End of received from server:-----------\n");
    printf(RESET);
    write(1, GREEN, SIZE_COLOUR);
    write(1, "[LOGGING LIBRARY] : ", strlen("[LOGGING LIBRARY] : "));
    analyze_server_response(buffer);
    write(1, RESET, SIZE_RESET);
    printf(CYAN);
    printf("%s", CLIENT_PROMPT);
    printf(RESET);
    fflush(stdout);
    return SUCCESS;
}
