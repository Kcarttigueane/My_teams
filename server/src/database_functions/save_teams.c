/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_teams.c
*/

#include "../../include/server.h"

void save_teams_to_file(database_t* db)
{
    FILE* file = fopen("teams.json", "w");
    if (!file)
        return;

    fprintf(file, "[\n");

    team_t* team;
    bool first_team = true;

    LIST_FOREACH(team, &(db->teams), entries)
    {
        if (!first_team) {
            fprintf(file, ",\n");
        }
        first_team = false;

        fprintf(file, "  {\n");
        fprintf(file, "    \"uuid\": \"%s\",\n", team->uuid);
        fprintf(file, "    \"name\": \"%s\",\n", team->name);
        fprintf(file, "    \"description\": \"%s\",\n", team->description);
        fprintf(file, "    \"users_count\": %d,\n", team->users_count);

        fprintf(file, "    \"users\": [\n");
        for (int i = 0; i < team->users_count; ++i) {
            fprintf(file, "      \"%s\"%s\n", team->users[i],
                    (i < team->users_count - 1) ? "," : "");
        }
        fprintf(file, "    ]\n");

        fprintf(file, "  }");
    }

    fprintf(file, "\n]\n");

    fclose(file);
}
