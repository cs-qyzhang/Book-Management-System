/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : client_connect.c
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 客户端通过TCP连接远程数据库
 *
 */
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "connect_database.h"

bool connect_server(char *send, char *receieve)
{
    struct sockaddr_in addr;
    int sfd;
    size_t size;
    ssize_t num_bytes;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        fprintf("connect_server : socket creat failed!\n");
        return false;
    }

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port   = PORT_SERVER;
    if (inet_pton(AF_INET, IP_SERVER, &addr.sin_addr) <= 0)
    {
        fprintf("connect_server : inet_pton error!\n");
        return fasle;
    }

    if (connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in) == -1))
    {
        fprintf("connect_server : connect error!\n");
        return false;
    }

    sendto(sdf, send, strlen(send) * sizeof(char), 0, addr, sizeof(struct sockaddr_in));

    recvfrom(sdf, receieve, strlen(receive) * sizeof(char), 0, addr, sizeof(struct sockaddr_in));

    printf("%s\n", receive);

    return true;
}
