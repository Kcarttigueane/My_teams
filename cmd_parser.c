/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** test
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1000
#define MAX_ARGUMENTS 10
#define MAX_ARGUMENT_LENGTH 100

char *parse_quoted_string(char *str)
{
    char *arg = malloc(sizeof(char) * MAX_ARGUMENT_LENGTH);
    if (*str == '"') {
        str++;
        char *end = strchr(str, '"');
        if (end != NULL) {
            strncpy(arg, str, end - str);
            arg[end - str] = '\0';
        }
    }
    return arg;
}

char *parse_unquoted_string(char *str)
{
    char *end = strchr(str, ' ');
    if (end == NULL) {
        end = strchr(str, '\0');
    }
    char *arg = malloc(sizeof(char) * MAX_ARGUMENT_LENGTH);
    strncpy(arg, str, end - str);
    arg[end - str] = '\0';
    return arg;
}

char **parse_command(char *command)
{
    char **args = malloc(sizeof(char *) * MAX_ARGUMENTS);
    int i = 0;

    while (*command != '\0' && i < MAX_ARGUMENTS - 1) {
        while (*command == ' ' || *command == '\t' || *command == '\n')
            command++;
        if (*command == '\0')
            break;
        char *arg;
        if (*command == '"') {
            arg = parse_quoted_string(command);
            command += *arg ? (int)strlen(arg) + 2 : 1;
        } else {
            arg = parse_unquoted_string(command);
            command += strlen(arg);
        }
        args[i++] = arg;
    }
    args[i] = NULL;
    return args;
}

int main(void)
{
    char command[MAX_COMMAND_LENGTH] = "/use \"argument 1\" argument azerty \"a b c d\te f g h\"";
    char **args = parse_command(command);

    for (int i = 0; args[i] != NULL; i++) {
        printf("|%s|", args[i]);
    }

    free(args);

    return 0;
}
