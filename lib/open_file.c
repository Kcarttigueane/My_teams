/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** open_file.c
*/

#include "../include/server.h"

FILE* open_file(char* file_name, int control_socket, char* message)
{
    FILE* file = fopen(file_name, "rb");

    if (file == NULL) {
        dprintf(control_socket, message, file_name);
        return NULL;
    }
    return file;
}
