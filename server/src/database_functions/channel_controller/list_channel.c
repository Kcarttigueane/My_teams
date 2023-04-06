/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_channel.c
*/

#include "../../../include/server.h"

static void append_channels(database_t* db, char* json, char* team_uuid,
int *nb_channel)
{
    channel_t* channel;
    LIST_FOREACH(channel, &(db->channels), entries) {
        char *timestamp = timestamp_to_string(channel->created_at);
        if (strcmp(channel->team_uuid, team_uuid) == 0) {
            char channel_json[BUFFER_SIZE];
            snprintf(channel_json, BUFFER_SIZE,
            "\t{\n\t  \"channel_uuid\": \"%s\",\n\t  \"channel_name\": "
            "\"%s\",\n\t  \"channel_description\": \"%s\",\n\t  "
            "\"channel_team_uuid\": \"%s\",\n\t  "
            "\"channel_creator_uuid\": \"%s\",\n\t  "
            "\"channel_created_at\": \"%s\",\n\t  "
            "\"channel_nb_users\": \"%zu\"\n\t}",
            channel->uuid, channel->name, channel->description,
            channel->team_uuid, channel->creator_uuid,
            timestamp, channel->nb_users);
            strncat(json, channel_json, BUFFER_SIZE - strlen(json) - 1);
            *nb_channel += 1;
        }
    }
}

static bool append_channels_json(database_t* db, char* json, char* team_uuid)
{
    int nb_channels = 0;

    strncat(json,
            "  \"status\": 209,\n"
            "  \"message\": \"Channels list\",\n"
            "  \"channels\": [\n",
            BUFFER_SIZE - strlen(json) - 1);
    append_channels(db, json, team_uuid, &nb_channels);
    if (nb_channels == 0) {
        return false;
    }
    strncat(json, "   \n  ]\n", BUFFER_SIZE - strlen(json) - 1);
    return true;
}

char* list_channels(database_t* db, char *team_uuid)
{
    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (!json) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    if (!append_channels_json(db, json, team_uuid)) {
        memset(json, 0, BUFFER_SIZE);
        snprintf(json, BUFFER_SIZE, "{\n");
        strncat(json,
        "  \"status\": 209,\n"
        "  \"message\": \"Channels list\"\n",
        BUFFER_SIZE - strlen(json) - 1);
    }
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
