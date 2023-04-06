/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_teams.c
*/

#include "../../../include/server.h"

static void write_team_to_file(FILE* file, team_t* team)
{
    char* timestamp = timestamp_to_string(team->created_at);

    fprintf(file, "  {\n");
    fprintf(file, "    \"uuid\": \"%s\",\n", team->uuid);
    fprintf(file, "    \"name\": \"%s\",\n", team->name);
    fprintf(file, "    \"description\": \"%s\",\n", team->description);
    fprintf(file, "    \"users_count\": %d,\n", team->users_count);
    fprintf(file, "    \"created_at\": \"%s\",\n", timestamp);

    free(timestamp);

    fprintf(file, "    \"users\": [\n");
    for (int i = 0; i < team->users_count; ++i) {
        fprintf(file, "      \"%s\"%s\n", team->users[i],
                (i < team->users_count - 1) ? "," : "");
    }
    fprintf(file, "    ]\n");
    fprintf(file, "  }");
}

void save_teams_to_file(database_t* db)
{
    if (!is_team_list_empty(db)) return;
    FILE* file = fopen("libs/database/teams.json", "w");
    if (!file) return;

    fprintf(file, "[\n");
    team_t* team;
    bool first_team = true;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!first_team)
            fprintf(file, ",\n");
        first_team = false;

        write_team_to_file(file, team);
    }

    fprintf(file, "\n]\n");
    fclose(file);
}
