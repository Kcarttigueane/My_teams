/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** cmd_list
*/

#include "../include/client.h"
#include "../../include/utils.h"

const char *ENDPOINTS_LIST[] = {
    "/help",
    "/login",
    "/logout",
    "/users",
    "/user",
    "/send",
    "/messages",
    "/subscribe",
    "/subscribed",
    "/unsubscribe",
    "/use",
    "/create",
    "/list",
    "/info",
};

const size_t ENDPOINTS_LIST_SIZE = ARRAY_SIZE(ENDPOINTS_LIST);
