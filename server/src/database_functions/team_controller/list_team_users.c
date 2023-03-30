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
            "\t{\n\t  \"user_uuid\": \"%s\",\n\t  \"username\": "
            "\"%s\"\n\t},\n",
            user->uuid, user->username);
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
    strncat(json,
            "  \"status\": 236,\n"
            "  \"message\": \"Users subscribed to team\",\n",
            BUFFER_SIZE - strlen(json) - 1);
    snprintf(json + strlen(json), BUFFER_SIZE - strlen(json),
    "  \"team_uuid\": \"%s\",\n", team->uuid);
    strncat(json, "  \"users\": [\n", BUFFER_SIZE - strlen(json) - 1);
    append_subscribed_users_to_team(db, team, json);
    strncat(json, "  ]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* list_users_subscribed_to_team(database_t* db, char* team_uuid)
{
    team_t* team = find_team_by_uuid(db, team_uuid);
    if (!team)
        return NULL;

    char* json = malloc(BUFFER_SIZE * sizeof(char));
    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_subscribed_users_to_team_json(db, team, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
