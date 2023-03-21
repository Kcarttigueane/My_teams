/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** my_teams.h
*/

#pragma once

    #define ERROR 84
    #define SUCCESS 0
    #define FAILURE -1

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

    #define handle_error(msg) \
        do {                  \
            perror(msg);      \
            exit(ERROR);      \
        } while (0)
