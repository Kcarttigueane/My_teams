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

// const char* USERS_JSON_REP =
//     "{\n"
//     "  \"status\": 218,\n"
//     "  \"message\": \"Users list\",\n"
//     "  \"users\": [\n"
//     "       {\"username\": \"user1\", \"user_uuid\": \"user1_uuid\"},\n"
//     "       {\"username\": \"user2\", \"user_uuid\": \"user2_uuid\"}\n"
//     "   ]\n"
//     "}\n";
