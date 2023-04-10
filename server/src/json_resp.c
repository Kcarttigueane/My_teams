/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** json_resp.c
*/

#include "../include/server.h"

const char* HELP_JSON_RESP =
    "{\n"
    "  \"status\": 202,\n"
    "  \"message\": \"Help listed\",\n"
    "  \"data\":  [\n"
    "       \"/help\",\n"
    "       \"/login\",\n"
    "       \"/logout\",\n"
    "       \"/users\",\n"
    "       \"/user\",\n"
    "       \"/send\",\n"
    "       \"/messages\",\n"
    "       \"/subscribe\",\n"
    "       \"/subscribed\",\n"
    "       \"/unsubscribe\",\n"
    "       \"/use\",\n"
    "       \"/create\",\n"
    "       \"/list\",\n"
    "       \"/info\",\n"
    "   ]\n"
    "}\n";

const char* LOGIN_JSON_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Connection successful\",\n"
    "  \"username\": \"%s\",\n"
    "  \"user_uuid\": \"%s\"\n"
    "}\n";

const char* LOGOUT_JSON_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Logout successful\"\n"
    "  \"username\": \"%s\"\n"
    "  \"user_uuid\": \"%s\"\n"
    "}\n";

const char* USER_DETAILS_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"User information\"\n"
    "  \"username\": \"%s\"\n"
    "  \"user_uuid\": \"%s\"\n"
    "  \"is_logged_in\": %s\n"
    "}\n";

const char* SEND_MSG_JSON_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Message received successfully\",\n"
    "  \"recipient_uuid\": \"%s\",\n"
    "  \"message_body\": \"%s\"\n"
    "}\n";

const char* CREATE_TEAM_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Team created\",\n"
    "  \"team_uuid\": \"%s\",\n"
    "  \"team_name\": \"%s\",\n"
    "  \"team_description\": \"%s\"\n"
    "}\n";

const char* CREATE_CHANNEL_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Channel created\",\n"
    "  \"channel_uuid\": \"%s\",\n"
    "  \"channel_name\": \"%s\",\n"
    "  \"channel_description\": \"%s\"\n"
    "}\n";

const char* CREATE_THREAD_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Thread created\",\n"
    "  \"thread_uuid\": \"%s\",\n"
    "  \"thread_title\": \"%s\",\n"
    "  \"thread_message\": \"%s\"\n"
    "  \"related_channel_uuid\": \"%s\"\n"
    "  \"creator_uuid\": \"%s\"\n"
    "  \"timestamp\": \"%ld\"\n"
    "}\n";

const char* CREATED_REPLY_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Reply created\",\n"
    "  \"team_uuid\": \"%s\",\n"
    "  \"reply_body\": \"%s\",\n"
    "  \"creator_uuid\": \"%s\"\n"
    "  \"thread_uuid\": \"%s\"\n"
    "  \"timestamp\": \"%s\"\n"
    "}\n";

const char* INFO_TEAM_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Team listed\",\n"
    "  \"team_uuid\": \"%s\",\n"
    "  \"team_name\": \"%s\",\n"
    "  \"team_description\": \"%s\"\n"
    "  \"number_of_users\" \": \"%d\"\n"
    "  \"created_at\" \": \"%s\"\n"
    "}\n";

const char* INFO_CHANNEL_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Channel listed\",\n"
    "  \"channel_uuid\": \"%s\",\n"
    "  \"channel_name\": \"%s\",\n"
    "  \"channel_description\": \"%s\"\n"
    "  \"related_team_uuid\": \"%s\"\n"
    "  \"number_of_users\" \": \"%d\"\n"
    "  \"created_at\" \": \"%s\"\n"
    "}\n";

const char* INFO_THREAD_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Thread listed\",\n"
    "  \"thread_uuid\": \"%s\",\n"
    "  \"thread_title\": \"%s\",\n"
    "  \"thread_message\": \"%s\"\n"
    "  \"related_channel_uuid\": \"%s\"\n"
    "  \"creator_uuid\": \"%s\"\n"
    "  \"created_at\" \": \"%s\"\n"
    "}\n";

const char* INFO_USER_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Info User\",\n"
    "  \"username\": \"%s\",\n"
    "  \"user_uuid\": \"%s\"\n"
    "  \"is_logged_in\": %s\n"
    "}\n";

const char* SUBSCRIBE_TO_TEAM =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Subscribed to team and channels\",\n"
    "  \"user_uuid\": \"%s\",\n"
    "  \"team_uuid\": \"%s\"\n"
    "}\n";

const char *UNSUBSCRIBE_TO_TEAM =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Unsubscribed to team and channels\",\n"
    "  \"user_uuid\": \"%s\",\n"
    "  \"team_uuid\": \"%s\"\n"
    "}\n";

const char* UNKNOWN_USER_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Unknown user\",\n"
    "  \"user_uuid\": \"%s\"\n"
    "}\n";

const char *UNKNOWN_TEAM_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Unknown team\",\n"
    "  \"team_uuid\": \"%s\"\n"
    "}\n";

const char *UNKNOWN_CHANNEL_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Unknown channel\",\n"
    "  \"channel_uuid\": \"%s\"\n"
    "}\n";

const char *UNKNOWN_THREAD_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Unknown thread\",\n"
    "  \"thread_uuid\": \"%s\"\n"
    "}\n";

const char* NO_MESSAGES_RESP =
    "{\n"
    "  \"status\": %i,\n"
    "  \"message\": \"Message list\",\n"
    "  \"recipient_uuid\": \"%s\",\n"
    "  \"messages\": []\n"
    "}\n";
