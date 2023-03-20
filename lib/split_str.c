/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** split_str.c
*/

#include "../include/lib.h"

size_t count_tokens(const char* str, const char* delimiter)
{
    if (!str || !delimiter)
        return 0;

    size_t nb_token = 0;
    char* str_cpy = strdup(str);

    if (str_cpy == NULL)
        return 0;

    for (char* save = str_cpy; (strtok_r(save, delimiter, &save)); nb_token++)
        ;
    free(str_cpy);
    return nb_token;
}

char** split_str(char* str, char* delimiter)
{
    size_t token_count;
    if (str == NULL || (token_count = count_tokens(str, delimiter)) == 0 ||
    delimiter == NULL)
        return NULL;

    char* str_cpy = strdup(str);
    if (str_cpy == NULL)
        return NULL;

    char* save = str_cpy;
    char** words = malloc(sizeof(char*) * (token_count + 1));
    char* token;

    for (int i = 0; (token = strtok_r(save, delimiter, &save)); i++) {
        words[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(words[i], token);
    }
    words[token_count] = NULL;
    free(str_cpy);
    return words;
}
