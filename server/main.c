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

    user_t* user_kevin = create_user(&db, "kevin");
    user_t* user_tom = create_user(&db, "tom");
    user_t* user_amine = create_user(&db, "amine");

    // print_users(&db);

    save_users_to_file(&db);

    // load_users_from_file(&db);

    // print_users(&db);

    discussion_t* dis =
        create_discussion(&db, user_kevin->uuid, user_amine->uuid);

    // load_discussions_from_file(&db);

    // print_discussion_details(&db, "8581640b-8a1f-40d2-9521-21b22a70ea10");

    add_message_to_discussion(&db, user_kevin->uuid, user_amine->uuid, "Hello");
    add_message_to_discussion(&db, user_kevin->uuid, user_amine->uuid, "How are you?");
    add_message_to_discussion(&db, user_amine->uuid, user_kevin->uuid, "I'm fine, thanks");
    add_message_to_discussion(&db, user_kevin->uuid, user_amine->uuid, "And you?");

    // printf("dis uuid: %s\n", dis->uuid);
    print_discussion_details(&db, dis->uuid);

    save_discussions_to_file(&db);

    // if (initialize_server(&server_data) == ERROR)
    //     return handle_error("Server initialization failed");

    // server_loop(&server_data, &db);

    team_t* team = create_team(&db, "team1", "team1 description");
    team_t* team2 = create_team(&db, "team2", "team2 description");

    add_user_to_team(&db, team->uuid, user_kevin->uuid);
    add_user_to_team(&db, team->uuid, user_tom->uuid);

    create_channel_params_t params = {
        .name = "channel1",
        .description = "channel1 description",
    };

    strcpy(params.team_uuid, team->uuid);
    strcpy(params.creator_uuid, user_kevin->uuid);

    channel_t *channel1 = create_channel(&db, &params);


    add_user_to_channel(&db, channel1->uuid, user_kevin->uuid);
    add_user_to_channel(&db, channel1->uuid, user_tom->uuid);

    remove_user_from_channel(&db, channel1->uuid, user_kevin->uuid);
    list_teams(&db);

    create_thread_params_t params2 = {
        .title = "thread1",
        .message = "thread1 message",
    };

    strcpy(params2.related_channel_uuid, channel1->uuid);
    strcpy(params2.creator_uuid, user_kevin->uuid);


    thread_t* thread = create_thread(&db, &params2);



    save_teams_to_file(&db);

    printf("\nDISPLAY TEAM INFOR\n\n");
    display_team_info(&db, team->uuid);
    printf("DISPLAY CHANNEL INFOR\n\n");
    display_channel_info(&db, channel1->uuid);

    printf("DISPLAY THREAD INFOR\n\n");

    add_reply_to_thread(&db, thread->uuid, "Hello", user_kevin->uuid);
    add_reply_to_thread(&db, thread->uuid, "How are you?", user_kevin->uuid);
    add_reply_to_thread(&db, thread->uuid, "I'm fine, thanks", user_tom->uuid);
    add_reply_to_thread(&db, thread->uuid, "And you?", user_kevin->uuid);

    list_threads(&db);

    save_threads_to_file(&db);

    free_database(&db);
    return SUCCESS;
};
