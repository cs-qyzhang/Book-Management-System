/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : server_lisen.c
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 服务器监听
 *
 */
/*#include <arpa/inet.h>*/
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./connect_database.h"
#include "../login/login.h"
#include "../global_data.h"

#define RECV_MSG_LEN    500

bool listen_to_client()
{
    struct addrinfo hints, *res;
    char addr_buf[51];
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, PORT_SERVER, &hints, &res))
    {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    inet_ntop(AF_INET, &(((struct sockaddr_in *)res->ai_addr)->sin_addr), addr_buf, 50);
    printf("server ip: %s\n", addr_buf);

    int sfd;
    sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (bind(sfd, res->ai_addr, res->ai_addrlen) == -1)
    {
        perror("bind");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(res);

    if (listen(sfd, 3) == -1)
    {
        perror("listen");
        close(sfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_storage client_addr;
    socklen_t client_addr_len;
    client_addr_len = sizeof(struct sockaddr_storage);

    char recv_msg[51];
    size_t recv_len;
    recv_len = 50;
    while (true)
    {
        int connected_sfd;
        printf("begin accept...\n");
        connected_sfd = accept(sfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (connected_sfd == -1)
        {
            perror("accept");
            close(sfd);
            exit(EXIT_FAILURE);
        }

        connected = true;
        inet_ntop(AF_INET, &(((struct sockaddr_in *)&client_addr)->sin_addr), addr_buf, 50);
        printf("connected to client: %s!\n", addr_buf);

        while (true)
        {
            if (recv(connected_sfd, recv_msg, recv_len, 0) >= 0)
            {
                if (!strcmp(recv_msg, "login_request"))
                    login_authentication();
            }
            else
                break;
        }
        connected = false;
    }

    return 0;
}
