/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_channels.c
*/

#include "../../include/server.h"

void load_channels_from_file(database_t* db)
{
    FILE* file = fopen("libs/database/channels.json", "r");
    if (!file)
        return;

    char line[256];
    channel_t* current_channel = NULL;

    LIST_INIT(&db->channels);

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "{")) {
            current_channel = malloc(sizeof(channel_t));
            LIST_INSERT_HEAD(&db->channels, current_channel, entries);
            current_channel->nb_users = 0;
        } else if (strstr(line, "}")) {
            current_channel = NULL;
        } else if (current_channel) {
            char key[64], value[256];
            sscanf(line, " \"%[^\"]\": \"%[^\"]\"", key, value);

            if (strcmp(key, "uuid") == 0) {
                strcpy(current_channel->uuid, value);
            } else if (strcmp(key, "name") == 0) {
                strcpy(current_channel->name, value);
            } else if (strcmp(key, "description") == 0) {
                strcpy(current_channel->description, value);
            } else if (strcmp(key, "team_uuid") == 0) {
                strcpy(current_channel->team_uuid, value);
            } else if (strcmp(key, "creator_uuid") == 0) {
                strcpy(current_channel->creator_uuid, value);
            } else if (strcmp(key, "users") == 0) {
                size_t index = 0;
                while (sscanf(line, " \"%[^\"]\"", value) == 1) {
                    strcpy(current_channel->users[index], value);
                    index++;
                    fgets(line, sizeof(line), file);
                }
                current_channel->nb_users = index;
            }
        }
    }

    fclose(file);
}
