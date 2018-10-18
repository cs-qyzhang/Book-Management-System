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
#include <sys/socket.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "connect_database.h"

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
bool connect_to_server(char *send_msg, size_t send_len, char *recv_msg, size_t recv_len)
{
    struct sockaddr_in addr;
    int sfd;
    int byte_send, byte_recv;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        fprintf(stderr, "connect_server : socket creat failed!\n");
        return false;
    }

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port   = PORT_SERVER;
    if (inet_pton(AF_INET, IP_SERVER, &addr.sin_addr) <= 0)
    {
        fprintf(stderr, "connect_server : inet_pton error!\n");
        return false;
    }
    printf("inet_pton success!\n");

    if (connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
    {
        perror("connect");
        fprintf(stderr, "connect_server : connect error!\n");
        return false;
    }

    printf("connect success!\n");
    while (true)
    {
        byte_send = send(sfd, send, send_len, 0);
        printf("send finished\n");
        if (byte_send == -1)
        {
            fprintf(stderr, "connect_to_server : send error!\n");
            return false;
        }
        else if ((unsigned long)byte_send < send_len)
        {
            send_msg += byte_send / sizeof(char);
            send_len -= byte_send;
        }
        else
            break;
    }
    printf("send success!\n");

    byte_recv = recv(sfd, recv_msg, recv_len, 0);
    if (byte_recv == -1)
    {
        fprintf(stderr, "connect_to_server : recv error!\n");
        return false;
    }
    else if (byte_recv == 0)
    {
        fprintf(stderr, "connect_to_server : recv error! connection closed!\n");
        return false;
    }
    else
        ;

    printf("%s\n", recv_msg);
    return true;
}
