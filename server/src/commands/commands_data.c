/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** commands_data.c
*/

#include "../../include/server.h"
#include "../../../include/utils.h"

const command_t COMMANDS_DATA[] = {
    {"/help", help, HELP_DESCRIPTION, false},
    {"/login", login, LOGIN_DESCRIPTION, false},
    {"/logout", logout, LOGOUT_DESCRIPTION, true},
    {"/users", users, USERS_DESCRIPTION, true},
    {"/user", user, USER_DESCRIPTION, true},
    {"/send", send_msg, SEND_DESCRIPTION, true},
    {"/messages", msgs, MSGS_DESCRIPTION, true},
    {"/subscribe", subscribe, SUBSCRIBE_DESCRIPTION, true},
    {"/subscribed", subscribed, SUBSCRIBED_DESCRIPTION, true},
    {"/unsubscribe  ", unsubscribe, UNSUBSCRIBE_DESCRIPTION, true},
    {"/use", use, USE_DESCRIPTION, true},
    {"/create", create, CREATE_DESCRIPTION, true},
    {"/list", list, LIST_DESCRIPTION, true},
    {"/info", info, INFO_DESCRIPTION, true},
};

const size_t COMMANDS_DATA_SIZE = ARRAY_SIZE(COMMANDS_DATA);
