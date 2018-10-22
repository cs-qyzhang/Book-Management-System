/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : connect_to_library.c
 * author      : qiuyang Zhang
 * created     : 2018/10/19
 * description : 连接图书馆服务器
 *
 */
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../global_data.h"
#include "./connect_database.h"

bool
connect_to_library(const char url[], const char filename[])
{
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo("ftp.lib.hust.edu.cn", "http", &hints, &res))
    {
        perror("connect_to_library : getaddrinfo");
        return false;
    }

    sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sfd == -1)
    {
        perror("connect_to_library : socket");
        return false;
    }
    if (connect(sfd, res->ai_addr, res->ai_addrlen))
    {
        perror("connect_to_library : connect");
        close(sfd);
        return false;
    }

    FILE *recv_file;
    recv_file = fopen(filename, "w+");
    if (recv_file == NULL)
    {
        perror("connect_to_library : fopen");
        close(sfd);
        return false;
    }

    char addr_buf[51];
    inet_ntop(AF_INET, &(((struct sockaddr_in *)res->ai_addr)->sin_addr), addr_buf, 50);
    freeaddrinfo(res);
    printf("connect to libraray: %s!\n", addr_buf);
    char send_msg[501];
    sprintf(send_msg, \
        "GET %s HTTP/1.0\r\n"
        //"Transfer-Encoding: chunked\r\n"
        "Host: ftp.lib.hust.edu.cn\r\n\r\n",
        //"Upgrade-Insecure-Requests: 1\r\n"
        //"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.67 Safari/537.36\r\n"
        //"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
       // "Accept-Encoding: gzip, deflate\r\n"
        //"Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        //"Cookie: III_EXPT_FILE=aa22527; III_SESSION_ID=57936ce2c85b5602a63fd99f018fbadb; SESSION_SCOPE=0; SESSION_LANGUAGE=chx\r\n"
        //"Cache-Control: no-cache\r\n\r\n",
        /*"Host: ftp.lib.hust.edu.cn\r\n"*/
        /*"User-Agent: Mozilla/5.0(X11; Linux x86_64)\r\n"*/
        /*"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,/;q=0.8;charset=UTF-8\r\n"*/
        /*"Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n"*/
        /*"Connection: keep-alive\r\n\r\n",*/
        url);

    send(sfd, send_msg, strlen(send_msg) * sizeof(char), 0);

    char recv_msg[1005];
    size_t recv_len;
    while (true)
    {
        if((recv_len = recv(sfd, recv_msg, 1000, 0)) <= 0)
            break;
        fwrite(recv_msg, recv_len, sizeof(char), recv_file);
    }

    printf("finished!\n");
    close(sfd);
    fclose(recv_file);

    return true;
}

