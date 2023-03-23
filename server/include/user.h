/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user.h
*/

#pragma once

typedef struct user_s {
    char uuid[MAX_UUID_STR_LEN];
    char username[MAX_NAME_LENGTH];
    LIST_ENTRY(user_s) entries;
} user_t;

bool check_user_already_exist(char* username);
bool add_user(struct user_list* users, char* uuid, char* username);
void print_users();
void delete_user(char* uuid);
user_t* get_user_by_uuid(char* uuid);
