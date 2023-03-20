/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** my_strcat.c
*/

#include "../include/lib.h"

char* my_strcat(char* s1, char* s2)
{
    int sum_len = strlen(s1) + strlen(s2);
    char* result = malloc(sizeof(char) * (sum_len + 1));
    int i;
    int j;

    for (i = 0; s1[i] != '\0'; i++)
        result[i] = s1[i];
    for (j = 0; s2[j] != '\0'; j++)
        result[i + j] = s2[j];
    result[i + j] = '\0';
    return result;
}
