/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** save_channels.c
*/

#include "../../include/server.h"

void save_channels_to_file(database_t* db)
{
    FILE* file = fopen("channels.json", "w");
    if (!file)
        return;

    fprintf(file, "[\n");

    channel_t* channel;
    bool first_channel = true;

    LIST_FOREACH(channel, &(db->channels), entries)
    {
        if (!first_channel) {
            fprintf(file, ",\n");
        }
        first_channel = false;

        fprintf(file, "  {\n");
        fprintf(file, "    \"uuid\": \"%s\",\n", channel->uuid);
        fprintf(file, "    \"name\": \"%s\",\n", channel->name);
        fprintf(file, "    \"description\": \"%s\",\n", channel->description);
        fprintf(file, "    \"team_uuid\": \"%s\",\n", channel->team_uuid);
        fprintf(file, "    \"creator_uuid\": \"%s\",\n", channel->creator_uuid);

        fprintf(file, "    \"users\": [\n");
        for (size_t i = 0; i < channel->nb_users; i++) {
            if (i > 0) {
                fprintf(file, ",\n");
            }
            fprintf(file, "      \"%s\"", channel->users[i]);
        }
        fprintf(file, "\n    ]\n");

        fprintf(file, "  }");
    }

    fprintf(file, "\n]\n");

    fclose(file);
}
