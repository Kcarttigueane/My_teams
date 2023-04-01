/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** add_user_team.c
*/

#include "../../../include/server.h"

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
    if (team->users_count >= 10) {
        printf("Error: Maximum number of users in the team has been reached\n");
        return false;
    }
    strncpy(team->users[team->users_count], user_uuid, MAX_UUID_LENGTH);
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
    int user_index = -1;
    for (int i = 0; i < team->users_count; i++)
        if (!strcmp(team->users[i], user_uuid)) {
            user_index = i;
            break;
        }
    if (user_index == -1) {
        printf("Error: User does not exist in the team\n");
        return false;
    }
    for (int i = user_index; i < team->users_count - 1; i++)
        strncpy(team->users[i], team->users[i + 1], MAX_UUID_LENGTH);

    team->users_count--;
    return true;
}
