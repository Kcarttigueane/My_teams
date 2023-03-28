/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** create_team.c
*/

#include "../../../../include/color.h"
#include "../../../include/server.h"

static team_t* create_team_object(char* name, char* description)
{
    team_t* new_team = malloc(sizeof(team_t));

    if (new_team == NULL) {
        printf("Error: Failed to allocate memory for new team\n");
        return NULL;
    }

    char* team_uuid = generate_uuid();

    strncpy(new_team->uuid, team_uuid, MAX_UUID_STR_LEN);
    strncpy(new_team->name, name, MAX_NAME_LENGTH);
    strncpy(new_team->description, description, MAX_DESCRIPTION_LENGTH);
    new_team->users_count = 0;
    new_team->created_at = time(NULL);

    free(team_uuid);

    return new_team;
}

team_t* create_team(database_t* db, char* name, char* description)
{
    team_t* new_team = create_team_object(name, description);

    if (!new_team)
        return NULL;

    LIST_INSERT_HEAD(&(db->teams), new_team, entries);

    debug_team(new_team);

    return new_team;
}
