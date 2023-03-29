/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-jules.dutel
** File description:
** json_resp.c
*/

#include "../include/server.h"

const char* HELP_JSON_REP =
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

const char* LOGIN_JSON_REP =
    "{\n"
    "  \"status\": 200,\n"
    "  \"message\": \"Connection successful\",\n"
    "  \"username\": \"%s\",\n"
    "  \"user_uuid\": \"%s\"\n"
    "}\n";

const char* LOGOUT_JSON_REP =
    "{\n"
    "  \"status\": 201,\n"
    "  \"message\": \"Logout successful\"\n"
    "}\n";

const char* USER_DETAILS =
    "{\n"
    "  \"status\": 204,\n"
    "  \"message\": \"User information\"\n"
    "  \"username\": \"%s\"\n"
    "  \"user_uuid\": \"%s\"\n"
    "}\n";

const char* SEND_MSG_JSON_REP =
    "{\n"
    "  \"status\": 202,\n"
    "  \"message\": \"Message sent successfully\",\n"
    "  \"recipient_uuid\": \"%s\",\n"
    "  \"message_body\": \"%s\"\n"
    "}\n";

const char* CREATE_TEAM =
    "{\n"
    "  \"status\": 204,\n"
    "  \"message\": \"Team created\",\n"
    "  \"team_uuid\": \"%s\",\n"
    "  \"team_name\": \"%s\",\n"
    "  \"team_description\": \"%s\"\n"
    "}\n";

const char* CREATE_CHANNEL =
    "{\n"
    "  \"status\": 205,\n"
    "  \"message\": \"Channel created\",\n"
    "  \"channel_uuid\": \"%s\",\n"
    "  \"channel_name\": \"%s\",\n"
    "  \"channel_description\": \"%s\"\n"
    "}\n";

const char* CREATE_THREAD =
    "{\n"
    "  \"status\": 206,\n"
    "  \"message\": \"Thread created\",\n"
    "  \"thread_uuid\": \"%s\",\n"
    "  \"thread_title\": \"%s\",\n"
    "  \"thread_body\": \"%s\"\n"
    "  \"timestamp\": \"%ld\"\n"
    "}\n";

const char* CREATE_REPLY =
    "{\n"
    "  \"status\": 210,\n"
    "  \"message\": \"Reply created\",\n"
    "  \"reply_uuid\": \"%s\",\n"
    "  \"reply_body\": \"%s\",\n"
    "  \"timestamp\": \"%ld\"\n"
    "}\n";

const char* INFO_TEAM =
    "{\n"
    "  \"status\": 211,\n"
    "  \"message\": \"Team listed\",\n"
    "  \"team_uuid\": \"%s\",\n"
    "  \"team_name\": \"%s\",\n"
    "  \"team_description\": \"%s\"\n"
    "  \"number_of_users\" \": \"%d\"\n"
    "  \"created_at\" \": \"%s\"\n"
    "}\n";

const char* INFO_CHANNEL =
    "{\n"
    "  \"status\": 212,\n"
    "  \"message\": \"Channel listed\",\n"
    "  \"channel_uuid\": \"%s\",\n"
    "  \"channel_name\": \"%s\",\n"
    "  \"channel_description\": \"%s\"\n"
    "  \"related_team_uuid\": \"%s\"\n"
    "  \"number_of_users\" \": \"%d\"\n"
    "  \"created_at\" \": \"%s\"\n"
    "}\n";

const char* INFO_THREAD =
    "{\n"
    "  \"status\": 213,\n"
    "  \"message\": \"Thread listed\",\n"
    "  \"thread_uuid\": \"%s\",\n"
    "  \"thread_title\": \"%s\",\n"
    "  \"thread_message\": \"%s\"\n"
    "  \"related_channel_uuid\": \"%s\"\n"
    "  \"creator_uuid\": \"%s\"\n"
    "  \"created_at\" \": \"%s\"\n"
    "}\n";

const char* INFO_USER =
    "{\n"
    "  \"status\": 213,\n"
    "  \"message\": \"Info User\",\n"
    "  \"username\": \"%s\",\n"
    "  \"user_uuid\": \"%s\"\n"
    "}\n";

const char* SUBSCRIBE_TO_TEAM =
    "{\n"
    "  \"status\": 214,\n"
    "  \"message\": \"Subscribed to team and channels\",\n"
    "  \"team_uuid\": \"%s\"\n"
    "}\n";

const char *UNSUBSCRIBE_TO_TEAM =
    "{\n"
    "  \"status\": 215,\n"
    "  \"message\": \"Unsubscribed to team and channels\",\n"
    "  \"team_uuid\": \"%s\"\n"
    "}\n";
