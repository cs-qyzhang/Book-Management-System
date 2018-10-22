/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : client_connect.c
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 客户端通过TCP连接远程数据库
 *
 */
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "./connect_database.h"
#include "../global_data.h"

void *get_in_addr(struct sockaddr * addr)
{
    if (addr->sa_family == AF_INET)
        return &(((struct sockaddr_in *)addr)->sin_addr);
    else
        return &(((struct sockaddr_in6 *)addr)->sin6_addr);
}

/*
 * 函数名称：connect_to_server
 * 函数功能：客户端连接服务器发送并接收信息
 * 函数输入：char *send_msg  : 要发送的信息
 *           size_t send_len : 要发送的信息的字节数
 *           char *recv_msg  : 接收信息存放的位置
 *           size_t recv_len : 接收信息缓冲区字节大小
 * 函数输出：bool
 * 函数说明：无
 * 创建时间：2018/10/17
 *
 */
bool connect_to_server()
{
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(IP_SERVER, PORT_SERVER, &hints, &res) == -1)
    {
        perror("getaddrinfo");
        return false;
    }

    int sfd;
    sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sfd == -1)
    {
        perror("socket");
        return false;
    }

    printf("begin connect...\n");
    if (connect(sfd, res->ai_addr, res->ai_addrlen) == -1)
    {
        perror("connect");
        close(sfd);
        return false;
    }

    connected = true;
    char buf[51];
    inet_ntop(res->ai_family, get_in_addr(res->ai_addr), buf, 50);
    freeaddrinfo(res);
    printf("connected to server: %s!\n", buf);

    return true;
}

bool
close_connection_to_server()
{
    if(close(sfd))
    {
        perror("close_connection_to_server : close");
        return false;
    }
    connected = false;
    return true;
}

bool
send_value(const char *value_name, const void *value)
{
    if (!connected)
        return false;

    char *msg;
    msg = value_write(value_name, value);

    send(sfd, msg, strlen(msg), 0);

    return false;
}

bool send_line(const char *msg)
{
    if (!connected)
        return false;

    char *send_msg;
    send_msg = (char *)malloc(strlen(msg) + strlen("\n") + 1);
    sprintf(send_msg, "%s\n", msg);
    send(sfd, send_msg, strlen(msg), 0);
    return true;
}
