/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** parse_json_resp.c
*/

#include "../include/client.h"

void parse_json_value(const char* json, const char* key, char* value,
size_t value_size)
{
    char format[64];
    snprintf(format, sizeof(format), "\"%s\": \"%%%lus\"", key, value_size - 1);

    int ret = sscanf(json, format, value);
    if (ret != 1) {
        value[0] = '\0';
    }
}
