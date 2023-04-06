/*
** EPITECH PROJECT, 2023
** STEP-1
** File description:
** main.c
*/

#pragma once

    #include <regex.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include <time.h>

// ! STR TO WORD ARRAY functions:

size_t count_tokens(const char* str, const char* delimiter);
char** split_str(char* str, char* delimiter);

// ! WORD ARRAY functions:

size_t get_size_word_array(char** array);
void free_word_array(char** map);

// ! FILE functions:

FILE* open_file(const char* filename, const char* mode);
char* read_file_contents(FILE* file);

// ! STRING functions:

char* my_strcat(char* s1, char* s2);
void send_error(int socket_fd, int status_code, const char* error_message);

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

// ! JSON functions:

bool extract_value(const char* key, char* json_str, char* value,
int max_length);

bool extract_boolean_value(const char* key, char* json_str, bool* value);

// ! TIME functions:

char* timestamp_to_string(time_t timestamp);
time_t string_to_timestamp(char* str);
