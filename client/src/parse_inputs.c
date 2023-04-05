/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** test
*/

#include "../include/client.h"

void free_tokens(char** tokens)
{
    for (int i = 0; i < MAX_TOKENS; i++)
        free(tokens[i]);
    free(tokens);
}

static char** allocate_and_copy_token(char** tokens, char* start,
int* token_count)
{
    tokens[*token_count] = malloc(strlen(start) + 1);
    strcpy(tokens[*token_count], start);
    (*token_count)++;
    return tokens;
}

static void initialize_buffer(char* buffer, char* command)
{
    strncpy(buffer, command, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';
}

static void process_space(char** tokens, char* cursor, char** start,
int* token_count)
{
    *cursor = '\0';
    tokens = allocate_and_copy_token(tokens, *start, token_count);
    *start = cursor + 1;
}

char** parse_inputs(char* command)
{
    char** tokens = calloc(MAX_TOKENS, sizeof(char*));
    char buffer[BUFFER_SIZE];
    initialize_buffer(buffer, command);
    int token_count = 0;
    bool in_quotes = false;
    char* start = buffer;
    for (char* cursor = buffer; *cursor != '\0'; cursor++) {
        in_quotes = *cursor == '"' ? !in_quotes : in_quotes;
        if (*cursor == ' ' && !in_quotes)
            process_space(tokens, cursor, &start, &token_count);
    }
    if (in_quotes) {
        printf("Error: Unmatched quotes\n");
        free(tokens);
        return NULL;
    }
    tokens = allocate_and_copy_token(tokens, start, &token_count);
    tokens[token_count] = NULL;
    return tokens;
}
