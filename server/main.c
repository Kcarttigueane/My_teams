/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** main.c
*/

#include "include/server.h"

int main(int argc, char const* argv[])
{
    if (!are_arguments_valid(argc, argv))
        return ERROR;

    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);

    server_data_t server_data = {
        .PORT = atoi(argv[1]),
        .socket_fd = 0,
        .readfds = {{0}},
    };

    database_t db = init_database();

    // create_user(&db, "1234", "kevin");
    // create_user(&db, "5678", "tom");
    // create_user(&db, "9012", "amine");

    // print_users(&db);

    // discussion_t *dis =  create_discussion(&db, "1234", "5678");

    // add_message_to_discussion(&db, "1234", "5678", "Hello");
    // add_message_to_discussion(&db, "1234", "5678", "How are you?");
    // add_message_to_discussion(&db, "1234", "5678", "I'm fine, thanks");
    // add_message_to_discussion(&db, "1234", "5678", "And you?");

    // print_discussion_details(&db, dis->uuid);

    // if (initialize_server(&server_data) == ERROR)
    //     return handle_error("Server initialization failed");

    // server_loop(&server_data, &db);

    free_users(&db);
    free_discussions(&db);

    return SUCCESS;
};
