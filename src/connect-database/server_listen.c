/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : server_lisen.c
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 服务器监听
 *
 */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "connect_database.h"

#define RECV_MSG_LEN    500

bool listen_to_client()
{
    int sfd, connected_sfd;
    struct sockaddr_in addr, connected_addr;
    socklen_t sock_len;
    int recv_byte, send_byte;
    size_t recv_len, send_len;
    char recv_msg[RECV_MSG_LEN];
    char *send_msg;

    recv_len = RECV_MSG_LEN;
    sock_len = sizeof(struct sockaddr_in);

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        fprintf(stderr, "listen_to_client : socket error!\n");
        return false;
    }

    memset(&addr, 0, sizeof(struct sockaddr_in));
    inet_pton(AF_INET, IP_SERVER, &addr.sin_addr);
    addr.sin_port = PORT_SERVER;
    bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    listen(sfd, 5);

    while (true)
    {
        printf("begin accept...\n");
        connected_sfd = accept(sfd, (struct sockaddr *)&connected_addr, &sock_len);
        printf("connect!\n");
        recv_byte = recv(sfd, recv_msg, recv_len, 0);

        send_len = strlen("great!") * sizeof(char);
        send_msg = (char *)malloc(send_len + 1);
        strcpy(send_msg, "great!");
        if (strcmp(recv_msg, "hello, socket!"))
            send_byte = send(sfd, send_msg, send_len, 0);
        close(connected_sfd);
        printf("closed!\n");
    }

    return 0;
}
