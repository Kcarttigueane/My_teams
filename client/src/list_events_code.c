/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** list_events_code.c
*/

#include "../include/client.h"
#include "../../include/utils.h"

const events_t LIST_EVENTS_CODE[] = {
    {CONNECTION_SUCCESSFUL, connection_successful},
    {DISCONNECTION_SUCCESSFUL, disconnection_successful},
    {MESSAGE_SENT, message_sent},
    {THREAD_REPLY_CREATED, thread_reply_created},
    {TEAM_CREATED, team_created},
    {CHANNEL_CREATED, channel_created},
    {THREAD_CREATED, thread_created},
    {PRINT_USERS, print_users},
    {PRINT_TEAMS, print_teams},
    {PRINT_CHANNELS, print_channels},
    {PRINT_THREADS, print_threads},
    {PRINT_THREAD_REPLIES, print_thread_replies},
    {PRINT_PRIVATE_MESSAGES, print_messages},
    {UNKNOWN_TEAM, unknow_team},
    {UNKNOWN_CHANNEL, unknow_channel},
    {UNKNOWN_THREAD, unknow_thread},
    {UNKNOWN_USER, unknow_user},
    {UNAUTHORIZED, unauthorized},
    {ALREADY_EXISTS, user_already_exist},
    {INFO_USER, info_user},
    {INFO_TEAM, info_team},
    {INFO_CHANNEL, info_channel},
    {INFO_THREAD, info_thread},
    {TEAM_CREATED_NOTIFICATION, team_created_notification},
    {CHANNEL_CREATED_NOTIFICATION, channel_created_notification},
    {THREAD_CREATED_NOTIFICATION, thread_created_notification},
    {REPLY_CREATED_NOTIFICATION, reply_created_notification},
    {SUBSCRIBED_TO_TEAM, subscribed_to_team},
    {UNSUBSCRIBED_FROM_TEAM, unsubscribed_from_team},
    {INTERNAL_SERVER_ERROR, internal_server_error},
    {NOT_IMPLEMENTED, not_implemented},
};

const size_t LIST_EVENTS_CODE_SIZE = ARRAY_SIZE(LIST_EVENTS_CODE);
