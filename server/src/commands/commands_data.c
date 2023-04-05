/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** commands_data.c
*/

#include "../../../include/utils.h"
#include "../../include/server.h"

const command_t COMMANDS_DATA[] = {
    {"/help", help, HELP_DESCRIPTION, false, {0, -1}},
    {"/login", login, LOGIN_DESCRIPTION, false, {1, -1}},
    {"/logout", logout, LOGOUT_DESCRIPTION, true, {0, -1}},
    {"/users", users, USERS_DESCRIPTION, true, {0, -1}},
    {"/user", user, USER_DESCRIPTION, true, {1, -1}},
    {"/send", send_msg, SEND_DESCRIPTION, true, {2, -1}},
    {"/messages", msgs, MSGS_DESCRIPTION, true, {1, -1}},
    {"/subscribe", subscribe, SUBSCRIBE_DESCRIPTION, true, {1, -1}},
    {"/subscribed", subscribed, SUBSCRIBED_DESCRIPTION, true, {0, 1, -1}},
    {"/unsubscribe", unsubscribe, UNSUBSCRIBE_DESCRIPTION, true, {1, -1}},
    {"/use", use, USE_DESCRIPTION, true, {0, 1, 2, 3, -1}},
    {"/create", create, CREATE_DESCRIPTION, true, {1, 2, -1}},
    {"/list", list, LIST_DESCRIPTION, true, {0, -1}},
    {"/info", info, INFO_DESCRIPTION, true, {0, -1}},
};

const size_t COMMANDS_DATA_SIZE = ARRAY_SIZE(COMMANDS_DATA);
