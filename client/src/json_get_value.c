/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** parse_json_resp.c
*/

#include "../include/client.h"

bool extract_value(const char* key, char* json_str, char* value, int max_length)
{
    int key_len = strlen(key);
    char search_key[key_len + 4];
    sprintf(search_key, "\"%s\": \"", key);

    char* ptr = strstr(json_str, search_key);
    if (ptr == NULL) {
        printf("Error: %s not found\n", key);
        return false;
    }
    ptr += strlen(search_key);
    strncpy(value, ptr, max_length);
    value[strcspn(value, "\"")] = '\0';
    return true;
}

bool extract_boolean_value(const char* key, char* json_str, bool* value)
{
    int key_len = strlen(key);
    char search_key[key_len + 4];
    sprintf(search_key, "\"%s\": ", key);

    char* ptr = strstr(json_str, search_key);
    if (ptr == NULL) {
        printf("Error: %s not found\n", key);
        return false;
    }
    ptr += strlen(search_key);
    if (strncmp(ptr, "true", 4) == 0) {
        *value = true;
    } else if (strncmp(ptr, "false", 5) == 0) {
        *value = false;
    } else {
        printf("Error: invalid %s value\n", key);
        return false;
    }
    return true;
}
