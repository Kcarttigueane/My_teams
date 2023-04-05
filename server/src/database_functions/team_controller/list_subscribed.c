/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_subscribed.c
*/

#include "../../../include/server.h"

static ssize_t find_user_in_team(team_t* team, const char* user_uuid)
{
    for (int i = 0; i < team->users_count; i++)
        if (!strcmp(team->users[i], user_uuid))
            return (ssize_t)i;

    return FAILURE;
}

static void append_subscribed_teams(database_t* db, char* user_uuid, char* json)
{
    team_t* team;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (find_user_in_team(team, user_uuid) >= 0) {
            char team_json[BUFFER_SIZE];
            snprintf(team_json, BUFFER_SIZE,
            "\t{\n\t  \"team_uuid\": \"%s\",\n\t  \"team_name\": "
            "\"%s\"\n\t},\n",
            team->uuid, team->name);
            strncat(json, team_json, BUFFER_SIZE - strlen(json) - 1);
        }
    }

    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
}

static void append_subscribed_teams_json(database_t* db, char* user_uuid,
char* json)
{
    if (!is_team_list_empty(db)) {
        strncat(json,
        "  \"status\": 235,\n"
        "  \"message\": \"Subscribed teams list\"\n",
        BUFFER_SIZE - strlen(json) - 1);
        return;
    }
    strncat(json,
            "  \"status\": 235,\n"
            "  \"message\": \"Subscribed teams list\",\n"
            "  \"teams\": [\n",
            BUFFER_SIZE - strlen(json) - 1);
    append_subscribed_teams(db, user_uuid, json);
    strncat(json, "  ]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* list_subscribed_teams(database_t* db, char* user_uuid)
{
    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (!json) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_subscribed_teams_json(db, user_uuid, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
