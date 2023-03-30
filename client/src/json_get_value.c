/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** parse_json_resp.c
*/

#include "../include/client.h"

char* json_get_value(char* json_str, const char* key)
{
    char* ptr = strstr(json_str, key);
    if (ptr == NULL) {
        printf("Error: key not found\n");
        return NULL;
    }
    ptr += strlen(key) + strlen("\": \"");
    char* value_start = ptr;
    char* value_end = strchr(ptr, '\"');
    if (value_end == NULL) {
        printf("Error: invalid JSON format\n");
        return NULL;
    }
    size_t value_length = value_end - value_start;
    char* value = (char*)malloc(value_length + 1);
    strncpy(value, value_start, value_length);
    value[value_length] = '\0';
    return value;
}
