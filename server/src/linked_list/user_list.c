/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** user_list.c
*/

#include "../../include/server.h"

static user_t *create_user_object(char* username)
{
    user_t* new_user = (user_t *)malloc(sizeof(user_t));

    if (new_user == NULL) {
        printf("Error: Failed to allocate memory for new user\n");
        return false;
    }

    char* uuid_str = generate_uuid();
    strncpy(new_user->uuid, uuid_str, MAX_UUID_STR_LEN);
    strncpy(new_user->username, username, MAX_NAME_LENGTH);
    free(uuid_str);

    return new_user;
}

user_t *create_user(database_t* database, char* username)
{
    user_t* user;

    LIST_FOREACH(user, &database->users, entries) {
        if (!strcmp(user->username, username)) {
            printf("Error: Username already exists\n");
            return NULL;
        }
    }

    user_t* new_user = create_user_object(username);

    if (new_user == NULL) {
        printf("Error: Failed to create user object\n");
        return NULL;
    }

    LIST_INSERT_HEAD(&database->users, new_user, entries);

    // ** server_event_user_created(user->uuid, user->username); // ! LOGGING LIB

    printf("User created with UUID %s and username %s\n", new_user->uuid,
    username);
    return new_user;
}

static void append_users(database_t* db, char* json)
{
    user_t* user;
    LIST_FOREACH(user, &(db->users), entries)
    {
        char user_json[1024];
        snprintf(
            user_json, 1024,
            "\t{\n\t  \"username\": \"%s\",\n\t  \"user_uuid\": \"%s\"\n\t},\n",
            user->username, user->uuid);
        strncat(json, user_json, 1024 - strlen(json) - 1);
    }
    // Remove the trailing comma
    if (json[strlen(json) - 2] == ',') {
        json[strlen(json) - 2] = '\n';
        json[strlen(json) - 1] = '\0';
    }
}

static void append_users_json(database_t* db, char* json)
{
    strncat(json,
            "  \"status\": 203,\n"
            "  \"message\": \"Users listed\",\n"
            "  \"users\": [\n",
            1024 - strlen(json) - 1);
    append_users(db, json);
    strncat(json, "   \n]\n", 1024 - strlen(json) - 1);
}

char* print_users(database_t* db)
{
    char* json = malloc(1024 * sizeof(char));
    if (json == NULL) {
        printf("Error: Failed to allocate memory for JSON string\n");
        return NULL;
    }
    snprintf(json, 1024, "{\n");
    append_users_json(db, json);
    strncat(json, "}", 1024 - strlen(json) - 1);
    return json;
}

void free_users(database_t* db)
{
    user_t* user;

    while (!LIST_EMPTY(&db->users)) {
        user = LIST_FIRST(&db->users);
        LIST_REMOVE(user, entries);
        free(user);
    }
}

user_t* find_user_by_uuid(database_t* db, char* uuid)
{
    user_t* user;

    LIST_FOREACH(user, &db->users, entries) {
        printf("Comparing %s to %s\n", user->uuid, uuid);
        if (!strcmp(user->uuid, uuid))
            return user;
    }

    return NULL;
}

user_t* find_user_by_username(database_t* db, char* username)
{
    user_t* user;

    LIST_FOREACH(user, &db->users, entries) {
        if (!strcmp(user->username, username))
            return user;
    }

    return NULL;
}
