/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : client.c
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 客户端main
 *
 */
#include <stdio.h>
#include "connect-database/connect_database.h"
#include <string.h>

int main(int argc, char **argv)
{
    char send_msg[] = "hello, socket!";
    char recv_msg[51];

    connect_to_server(send_msg, strlen(send_msg) * sizeof(char), recv_msg, 50);
}

