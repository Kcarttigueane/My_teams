/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_team_users.c
*/

#include "../../../include/server.h"

static void append_subscribed_users_to_team(database_t* db, team_t* team,
char* json)
{
    for (int i = 0; i < team->users_count; i++) {
        user_t* user = find_user_by_uuid(db, team->users[i]);
        if (user != NULL) {
            char user_json[BUFFER_SIZE];
            snprintf(user_json, BUFFER_SIZE,
            "\t{\n\t  \"username\": \"%s\",\n\t  \"user_uuid\": "
            "\"%s\",\n\t  \"is_logged_in\": %s\n\t},\n",
            user->username, user->uuid,
            user->is_logged_in ? "true" : "false");
            strncat(json, user_json, BUFFER_SIZE - strlen(json) - 1);
        }
    }

    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
}

static void append_subscribed_users_to_team_json(database_t* db, team_t* team,
char* json)
{
    if (team->users_count == 0) {
        strncat(json,
        "  \"status\": 207,\n"
        "  \"message\": \"Users subscribed to team\"\n",
        BUFFER_SIZE - strlen(json) - 1);
        return;
    }
    strncat(json,
            "  \"status\": 207,\n"
            "  \"message\": \"Users subscribed to team\",\n",
            BUFFER_SIZE - strlen(json) - 1);
    snprintf(json + strlen(json), BUFFER_SIZE - strlen(json),
    "  \"team_uuid\": \"%s\",\n", team->uuid);
    strncat(json, "  \"users\": [\n", BUFFER_SIZE - strlen(json) - 1);
    append_subscribed_users_to_team(db, team, json);
    strncat(json, "  ]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* list_users_subscribed_to_team(database_t* db, team_t *team)
{
    char* json = malloc(BUFFER_SIZE * sizeof(char));
    if (json == NULL) {
        printf("Error: [Error]: Malloc failed\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_subscribed_users_to_team_json(db, team, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
