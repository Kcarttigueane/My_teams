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
        char team_json[1024];
        snprintf(team_json, 1024,
        "\t{\n\t  \"team_uuid\": \"%s\",\n\t  \"team_name\": "
        "\"%s\",\n\t  \"team_description\": \"%s\"\n\t},\n",
        team->uuid, team->name, team->description);
        strncat(json, team_json, 1024 - strlen(json) - 1);
    }

    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
}

static void append_teams_json(database_t* db, char* json)
{
    strncat(json,
            "  \"status\": 228,\n"
            "  \"message\": \"Teams list\",\n"
            "  \"teams\": [\n",
            1024 - strlen(json) - 1);
    append_teams(db, json);
    strncat(json, "   \n]\n", 1024 - strlen(json) - 1);
}

char* list_teams(database_t* db)
{
    char* json = malloc(1024 * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, 1024, "{\n");
    append_teams_json(db, json);
    strncat(json, "}", 1024 - strlen(json) - 1);

    return json;
}
