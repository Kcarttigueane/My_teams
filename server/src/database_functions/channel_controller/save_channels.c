/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_channels.c
*/

#include "../../../include/server.h"

void write_channel_info(FILE* file, channel_t* channel)
{
    fprintf(file, "  {\n");
    fprintf(file, "    \"uuid\": \"%s\",\n", channel->uuid);
    fprintf(file, "    \"name\": \"%s\",\n", channel->name);
    fprintf(file, "    \"description\": \"%s\",\n", channel->description);
    fprintf(file, "    \"team_uuid\": \"%s\",\n", channel->team_uuid);
    fprintf(file, "    \"creator_uuid\": \"%s\",\n", channel->creator_uuid);
    fprintf(file, "    \"nb_users\": %li,\n", channel->nb_users);
    fprintf(file, "    \"created_at\": %ld,\n", channel->created_at);
}

void write_channel_users(FILE* file, channel_t* channel)
{
    fprintf(file, "    \"users\": [\n");

    for (size_t i = 0; i < channel->nb_users; i++) {
        if (i > 0) {
            fprintf(file, ",\n");
        }
        fprintf(file, "      \"%s\"", channel->users[i]);
    }
    fprintf(file, "\n    ]\n");
}

void save_channels_to_file(database_t* db)
{
    FILE* file = fopen("libs/database/channels.json", "w");
    if (!file) return;

    fprintf(file, "[\n");

    channel_t* channel;
    bool first_channel = true;

    LIST_FOREACH(channel, &(db->channels), entries) {
        if (!first_channel)
            fprintf(file, ",\n");
        first_channel = false;
        write_channel_info(file, channel);
        write_channel_users(file, channel);
        fprintf(file, "  }");
    }
    fprintf(file, "\n]\n");

    fclose(file);
}
