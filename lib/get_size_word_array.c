/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** get_size_word_array.c
*/
#include "../include/lib.h"

size_t get_size_word_array(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}
