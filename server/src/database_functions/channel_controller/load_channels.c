/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** load_channels.c
*/

#include "../../../include/server.h"

static channel_t* create_new_channel(database_t* db)
{
    channel_t* channel = (channel_t*)malloc(sizeof(channel_t));
    LIST_INSERT_HEAD(&db->channels, channel, entries);
    channel->nb_users = 0;
    return channel;
}

void load_channel_users(channel_t* channel, char* line, FILE* file)
{
    size_t index = 0;
    char value[256];
    while (sscanf(line, " \"%[^\"]\"", value) == 1) {
        strcpy(channel->users[index], value);
        index++;
        fgets(line, sizeof(line), file);
    }
    channel->nb_users = index;
}

static void set_channel_field(channel_t* channel, char* line, FILE* file)
{
    char key[64], value[256];
    sscanf(line, " \"%[^\"]\": \"%[^\"]\"", key, value);

    !strcmp(key, "uuid") ? strcpy(channel->uuid, value)
    : !strcmp(key, "name") ? strcpy(channel->name, value)
    : !strcmp(key, "description") ? strcpy(channel->description, value)
    : !strcmp(key, "team_uuid") ? strcpy(channel->team_uuid, value)
    : !strcmp(key, "creator_uuid") ? strcpy(channel->creator_uuid, value)
    : !strcmp(key, "users") ? load_channel_users(channel, line, file)
    : (void)0;
}

void load_channels_from_file(database_t* db)
{
    FILE* file = fopen("libs/database/channels.json", "r");
    if (!file)
        return;

    char line[256];
    channel_t* current_channel = NULL;

    LIST_INIT(&db->channels);

    while (fgets(line, sizeof(line), file)) {
        is_start_json(line) ? current_channel = create_new_channel(db)
        : is_end_json(line) ? current_channel = NULL
        : current_channel ? set_channel_field(current_channel, line, file)
        : (void)0;
    }

    fclose(file);
}
