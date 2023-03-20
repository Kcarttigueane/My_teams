/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** debug_command.c
*/

#include <unistd.h>
#include "../include/server.h"
#include "../include/color.h"

// void debug_command(char* buffer)
// {
//     for (size_t i = 0; i < (strlen(buffer) - 1); i++) {
//         if (buffer[i] == CARRIAGE_RETURN && buffer[i + 1] == LINE_FEED) {
//             write(0, GREEN, SIZE_COLOUR);
//             write(0, "CRLF\n", 5);
//             write(0, RESET, SIZE_RESET);
//             i++;
//         } else {
//             write(0, &buffer[i], 1);
//         }
//     }
// }
