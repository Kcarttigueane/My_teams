/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** teams.c
*/

#include "../../include/server.h"

team_t* create_team(database_t* db, char* name, char* description)
{
    team_t* new_team = malloc(sizeof(team_t));

    if (new_team == NULL) {
        printf("Error: Failed to allocate memory for new team\n");
        return NULL;
    }

    char *team_uuid = generate_uuid();
    strncpy(new_team->uuid, team_uuid, MAX_UUID_STR_LEN);
    strncpy(new_team->name, name, MAX_NAME_LENGTH);
    strncpy(new_team->description, description, MAX_DESCRIPTION_LENGTH);
    new_team->users_count = 0;
    new_team->created_at = time(NULL);
    free(team_uuid);

    LIST_INSERT_HEAD(&(db->teams), new_team, entries);

    return new_team;
}

void list_teams(database_t* db)
{
    team_t* team;

    printf("Teams in the database:\n");

    LIST_FOREACH(team, &(db->teams), entries) {
        printf("- Name: %s\n", team->name);
        printf("  Description: %s\n", team->description);
        printf("  Users:\n");
        printf("  Current Unix timestamp: %ld\n", (long)team->created_at);

        for (int i = 0; i < team->users_count; i++) {
            printf("    - %s\n", team->users[i]);
        }
    }
}

void free_teams(database_t* db)
{
    team_t* team;
    team_t *tmp;

    LIST_FOREACH_SAFE(team, &(db->teams), entries, tmp) {
        LIST_REMOVE(team, entries);
        free(team);
    }
}

bool is_team_exists(database_t* db, char* team_uuid)
{
    team_t* team;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!strcmp(team->uuid, team_uuid))
            return true;
    }

    return false;
}

void display_team_info(database_t* db, char* team_uuid)
{
    team_t* team = NULL;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!strcmp(team->uuid, team_uuid))
            break;
    }

    if (team == NULL) {
        printf("Error: Team not found\n");
        return;
    }

    printf("Team UUID: %s\n", team->uuid);
    printf("Team name: %s\n", team->name);
    printf("Team description: %s\n", team->description);
    printf("Team created at: %ld\n", (long)team->created_at);
    printf("Team users:\n");

    for (int i = 0; i < team->users_count; i++)
        printf("- %s\n", team->users[i]);
}

team_t *find_team_by_uuid(database_t *db, char *team_uuid)
{
    team_t *team = NULL;

    LIST_FOREACH(team, &(db->teams), entries) {
        if (!strcmp(team->uuid, team_uuid))
            break;
    }

    return team;
}

bool add_user_to_team(database_t* db, char* team_uuid, char* user_uuid)
{
    team_t* team = find_team_by_uuid(db, team_uuid);

    if (team == NULL) {
        printf("Error: Team not found\n");
        return false;
    }

    for (int i = 0; i < team->users_count; i++) {
        if (!strcmp(team->users[i], user_uuid)) {
            printf("Error: User already exists in the team\n");
            return false;
        }
    }

    // Add the user to the team
    if (team->users_count >= 10) {
        printf("Error: Maximum number of users in the team has been reached\n");
        return false;
    }

    strncpy(team->users[team->users_count], user_uuid, MAX_UUID_STR_LEN);
    team->users_count++;

    return true;
}

bool remove_user_from_team(database_t* db, char* team_uuid, char* user_uuid)
{
    team_t* team = find_team_by_uuid(db, team_uuid);

    if (team == NULL) {
        printf("Error: Team not found\n");
        return false;
    }

    // Check if the user exists in the team
    int user_index = -1;
    for (int i = 0; i < team->users_count; i++) {
        if (!strcmp(team->users[i], user_uuid)) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        printf("Error: User does not exist in the team\n");
        return false;
    }

    // Remove the user from the team
    for (int i = user_index; i < team->users_count - 1; i++) {
        strncpy(team->users[i], team->users[i + 1], MAX_UUID_STR_LEN);
    }
    team->users_count--;

    return true;
}
