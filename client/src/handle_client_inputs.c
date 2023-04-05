/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** handle_client_inputs.c
*/

#include "../include/client.h"

static void append_character(char* dest, char c)
{
    size_t len = strlen(dest);
    dest[len] = c;
    dest[len + 1] = '\0';
}

static char* convert_2d_array_to_string(char** words)
{
    size_t total_length = 0;
    for (int i = 0; words[i] != NULL; i++)
        total_length += strlen(words[i]) + 1;

    char* result = malloc(total_length + 1);
    result[0] = '\0';

    for (int i = 0; words[i] != NULL; i++) {
        if (i > 0)
            strcat(result, "\n");

        for (char* p = words[i]; *p != '\0'; p++) {
            (*p != '"') ? append_character(result, *p) : 0;
        }
    }
    return result;
}

static bool is_quoted_arg(const char* arg)
{
    int len = strlen(arg);
    return (len >= 2 && arg[0] == '"' && arg[len - 1] == '"');
}

static bool check_quoted_args(char** args)
{
    for (int i = 1; args[i] != NULL; i++) {
        if (!is_quoted_arg(args[i])) {
            printf("Missing quotes around argument %d: %s\n", i, args[i]);
            return false;
        }
    }
    return true;
}

int handle_user_input(client_data_t* client)
{
    char buffer[BUFFER_SIZE] = {0};
    if (!fgets(buffer, BUFFER_SIZE, stdin)) return SUCCESS;

    size_t len = strcspn(buffer, "\n");
    buffer[len] = '\0';

    char** words = parse_inputs(buffer);
    if (!words) return 0;

    if (!check_quoted_args(words)) {
        printf(
        "Invalid arguments => args should be quoted with doubled quotes\n");
        free_tokens(words);
        return SUCCESS;
    }
    char *string_to_send = convert_2d_array_to_string(words);
    send(client->socket_fd, string_to_send, strlen(string_to_send), 0);
    free_tokens(words);
    free(string_to_send);
    return SUCCESS;
}
