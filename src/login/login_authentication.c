/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : login_authentication.c
 * author      : qiuyang Zhang
 * created     : 2018/10/21
 * description : 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "../connect-database/connect_database.h"
#include "../data-structure/user.h"
#include "../global_data.h"
#include "../user-management/search_user.h"

void
login_authentication()
{
    if (!connected)
        return;

    char recv_msg[VALUE_NAME_LEN + VALUE_LEN + 1];

    char *value_name = NULL;
    void *value = NULL;
    
    recv(sfd, recv_msg, VALUE_NAME_LEN + VALUE_LEN + 1, 0);

    if (!value_read(recv_msg, value_name, value))
    {
        fprintf(stderr, "login_authentication : value_read error!\n");
        return;
    }

    User user_search;
    if (!strcmp(value_name, "job_id"))
    {
        user_search.job_id = value;
        user_search.username = NULL;
    }
    else
    {
        user_search.username = value;
        user_search.job_id = NULL;
    }

    recv(sfd, recv_msg, VALUE_NAME_LEN + VALUE_LEN + 1, 0);

    if (!value_read(recv_msg, value_name, value))
    {
        fprintf(stderr, "login_authentication : value_read error!\n");
        return;
    }

    user_search.password = value;

    recv(sfd, recv_msg, VALUE_NAME_LEN + VALUE_LEN + 1, 0);

    if (!value_read(recv_msg, value_name, value))
    {
        fprintf(stderr, "login_authentication : value_read error!\n");
        return;
    }

    user_search.root = *(bool *)value;

    if (search_user(&user_search) != NULL)
        send(sfd, "true\n", strlen("true\n"), 0);
    else
        send(sfd, "false\n", strlen("false\n"), 0);

    return ;
}
