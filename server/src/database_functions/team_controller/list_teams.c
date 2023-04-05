/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_teams.c
*/

#include "../../../include/server.h"

static void append_teams(database_t* db, char* json)
{
    team_t* team;

    LIST_FOREACH(team, &(db->teams), entries) {
        debug_team(team);
        char team_json[BUFFER_SIZE];
        snprintf(team_json, BUFFER_SIZE,
        "\t{\n\t  \"team_uuid\": \"%s\",\n\t  \"team_name\": "
        "\"%s\",\n\t  \"team_description\": \"%s\",\n\t"
        "  \"created_at\": \"%ld\"\n\t},\n",
        team->uuid, team->name, team->description,
        (long)team->created_at);
        strncat(json, team_json, BUFFER_SIZE - strlen(json) - 1);
    }

    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
}

static void append_teams_json(database_t* db, char* json)
{
    strncat(json,
            "  \"status\": 208,\n"
            "  \"message\": \"Teams list\",\n"
            "  \"teams\": [\n",
            BUFFER_SIZE - strlen(json) - 1);
    append_teams(db, json);
    strncat(json, "  ]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* list_teams(database_t* db)
{
    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_teams_json(db, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
