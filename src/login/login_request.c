/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : login_request.c
 * author      : qiuyang Zhang
 * created     : 2018/10/18
 * description : 登录请求
 *
 */
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include "../global_data.h"
#include "../connect-database/connect_database.h"
#include "../data-structure/user.h"

bool
login_request(User *user_info)
{
    if (user_info->job_id == NULL && user_info->username == NULL)
        return false;

    if (!connect_to_server())
    {
        printf("login_request : connect_to_server error!\n");
        return false;
    }
    send_line("login_request");
    if (user_info->job_id != NULL)
        send_value("job_id", user_info->job_id);
    else
        send_value("username", user_info->job_id);

    send_value("password", user_info->password);
    send_value("root", &user_info->root);

    char recv_msg[11];
    recv(sfd, recv_msg, 10, 0);
    printf("%s\n", recv_msg);

    close_connection_to_server();

    if (!strcmp(recv_msg, "true"))
        return true;
    else
        return false;
}
