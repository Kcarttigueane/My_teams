/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** free_word_array.c
*/

#include "../include/lib.h"

void free_word_array(char** map)
{
    if (!map)
        return;

    for (int i = 0; map[i] != NULL; i++)
        free(map[i]);
    free(map);
}
