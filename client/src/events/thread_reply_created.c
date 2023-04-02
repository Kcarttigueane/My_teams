/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** thread_reply_created.c
*/

#include "../../include/client.h"

void thread_reply_created(char* json_response)
{
    char *creator_uuid = json_get_value(json_response, "creator_uuid");
    char *reply_body = json_get_value(json_response, "reply_body");
    char *team_uuid = json_get_value(json_response, "team_uuid");
    char *thread_uuid = json_get_value(json_response, "thread_uuid");

    if (creator_uuid == NULL || reply_body == NULL || creator_uuid == NULL ||
    thread_uuid == NULL) {
        printf("Error: Invalid json response from server\n");
        return;
    }

    client_event_thread_reply_received(team_uuid, reply_body, thread_uuid,
    reply_body);

    free(creator_uuid);
    free(reply_body);
    free(team_uuid);
    free(thread_uuid);
}
