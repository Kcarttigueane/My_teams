/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** thread_reply_created.c
*/

#include "../../include/client.h"

void thread_reply_created(char* json_response)
{
    char creator_uuid[MAX_UUID_LENGTH] = {0};
    char reply_body[MAX_BODY_LENGTH] = {0};
    char team_uuid[MAX_UUID_LENGTH] = {0};
    char thread_uuid[MAX_UUID_LENGTH] = {0};

    if (!extract_value("creator_uuid", json_response, creator_uuid,
        sizeof(creator_uuid)) ||
        !extract_value("reply_body", json_response, reply_body,
        sizeof(reply_body)) ||
        !extract_value("team_uuid", json_response, team_uuid,
        sizeof(team_uuid)) ||
        !extract_value("thread_uuid", json_response, thread_uuid,
        sizeof(thread_uuid))) {
        printf("Error: invalid JSON format\n");
        return;
    }

    client_event_thread_reply_received(team_uuid, creator_uuid, thread_uuid,
    reply_body);
}
