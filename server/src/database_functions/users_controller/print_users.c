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
        char user_json[BUFFER_SIZE];
        snprintf(user_json, BUFFER_SIZE,
        "\t{\n\t  \"username\": \"%s\",\n\t  \"user_uuid\": "
        "\"%s\",\n\t  \"is_logged_in\": %s\n\t},\n",
        user->username, user->uuid,
        user->is_logged_in ? "true" : "false");
        strncat(json, user_json, BUFFER_SIZE - strlen(json) - 1);
    }

    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
}

static void append_users_json(database_t* db, char* json)
{
    strncat(json,
    "  \"status\": 207,\n"
    "  \"message\": \"Users listed\",\n"
    "  \"users\": [\n",
    BUFFER_SIZE - strlen(json) - 1);
    append_users(db, json);
    strncat(json, "  ]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* print_users(database_t* db)
{
    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_users_json(db, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
