/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** regex_match.c
*/

#include "lib.h"

bool regex_match(const char* pattern, const char* string)
{
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0)
        return false;

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return true;
    } else if (ret == REG_NOMATCH) {
        return false;
    } else {
        return false;
    }
}
