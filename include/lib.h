/*
** EPITECH PROJECT, 2023
** STEP-1
** File description:
** main.c
*/

#pragma once

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <stdbool.h>

size_t count_tokens(const char* str, const char* delimiter);
char** split_str(char* str, char* delimiter);

size_t get_size_word_array(char** array);
char* my_strcat(char* s1, char* s2);

void free_word_array(char** map);

FILE* open_file(const char* filename, const char* mode);

void send_error(int socket_fd, int status_code,
const char* error_message);

bool is_start_json(char* line);
bool is_end_json(char* line);

// ! DEBUG functions:

void debug_word_array(char** word_array);

int handle_error(const char* msg);
int handle_failure(const char* msg);

    // ! Regex functions:

bool regex_match(const char* pattern, const char* string);

// ! UUID functions:

char* generate_uuid(void);
