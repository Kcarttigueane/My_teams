/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** read_file_contents.c
*/

#include "../include/lib.h"

char* read_file_contents(FILE* file)
{
    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);

    if (file_size == 0)
        return NULL;

    rewind(file);

    char* buffer = malloc(file_size + 1);

    if (!buffer) return NULL;

    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0';

    return buffer;
}
