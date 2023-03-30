/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** open_file.c
*/

#include <stdio.h>

FILE* open_file(const char* filename, const char* mode)
{
    FILE* fp = fopen(filename, mode);

    if (fp == NULL) {
        fprintf(stdout, "Error opening file %s\n", filename);
        return NULL;
    }

    return fp;
}
