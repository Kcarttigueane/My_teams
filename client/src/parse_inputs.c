/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** test
*/

#include "../include/client.h"

char** parse_inputs(char* command)
{
    char** tokens = calloc(MAX_TOKENS, sizeof(char*));
    char buffer[BUFFER_SIZE];
    strncpy(buffer, command, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';

    int token_count = 0;
    bool in_quotes = false;
    char* start = buffer;
    for (char* cursor = buffer; *cursor != '\0'; cursor++) {
        if (*cursor == '"') {
            in_quotes = !in_quotes;
        } else if (*cursor == ' ' && !in_quotes) {
            *cursor = '\0';
            tokens[token_count] =
                malloc(strlen(start) + 1);  // Allocate memory for the word
            strcpy(tokens[token_count++],
                   start);  // Copy the word to the allocated memory
            start = cursor + 1;
        }
    }
    if (in_quotes) {
        fprintf(stderr, "Error: Unmatched quotes\n");
        free(tokens);
        return NULL;
    }

    tokens[token_count] =
        malloc(strlen(start) + 1);  // Allocate memory for the word
    strcpy(tokens[token_count++],
           start);  // Copy the word to the allocated memory
    tokens[token_count] = NULL;
    return tokens;
}
