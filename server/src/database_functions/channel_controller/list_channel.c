/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_channel.c
*/

#include "../../../include/server.h"

static void append_channels(database_t* db, char* json)
{
    channel_t* channel;

    LIST_FOREACH(channel, &(db->channels), entries) {
        debug_channel(channel);
        char channel_json[BUFFER_SIZE];
        snprintf(channel_json, BUFFER_SIZE,
        "\t{\n\t  \"channel_uuid\": \"%s\",\n\t  \"channel_name\": "
        "\"%s\",\n\t  \"channel_description\": \"%s\",\n\t  "
        "\"channel_team_uuid\": \"%s\",\n\t  "
        "\"channel_creator_uuid\": \"%s\",\n\t  "
        "\"channel_created_at\": \"%ld\",\n\t  "
        "\"channel_nb_users\": \"%zu\"\n\t}",
        channel->uuid, channel->name, channel->description,
        channel->team_uuid, channel->creator_uuid,
        (long)channel->created_at, channel->nb_users);
        strncat(json, channel_json, BUFFER_SIZE - strlen(json) - 1);
    }
}

static void append_channels_json(database_t* db, char* json)
{
    strncat(json,
            "  \"status\": 228,\n"
            "  \"message\": \"Channels list\",\n"
            "  \"channels\": [\n",
            BUFFER_SIZE - strlen(json) - 1);
    append_channels(db, json);
    strncat(json, "   \n  ]\n", BUFFER_SIZE - strlen(json) - 1);
}

char* list_channels(database_t* db)
{
    char* json = malloc(BUFFER_SIZE * sizeof(char));

    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }

    snprintf(json, BUFFER_SIZE, "{\n");
    append_channels_json(db, json);
    strncat(json, "}", BUFFER_SIZE - strlen(json) - 1);

    return json;
}
