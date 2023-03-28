/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** print_users.c
*/

#include "../../../include/server.h"

static void append_users(database_t* db, char* json)
{
    user_t* user;

    LIST_FOREACH(user, &(db->users), entries) {
        char user_json[1024];
        snprintf(
            user_json, 1024,
            "\t{\n\t  \"username\": \"%s\",\n\t  \"user_uuid\": \"%s\"\n\t},\n",
            user->username, user->uuid);
        strncat(json, user_json, 1024 - strlen(json) - 1);
    }

    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
}

static void append_users_json(database_t* db, char* json)
{
    strncat(json,
            "  \"status\": 203,\n"
            "  \"message\": \"Users listed\",\n"
            "  \"users\": [\n",
            1024 - strlen(json) - 1);
    append_users(db, json);
    strncat(json, "   \n]\n", 1024 - strlen(json) - 1);
}

char* print_users(database_t* db)
{
    char* json = malloc(1024 * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, 1024, "{\n");
    append_users_json(db, json);
    strncat(json, "}", 1024 - strlen(json) - 1);

    return json;
}
