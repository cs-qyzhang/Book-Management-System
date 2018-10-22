/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : global_data.c
 * author      : qiuyang Zhang
 * created     : 2018/10/18
 * description : 全局变量定义
 *
 */
#include <stdbool.h>
#include <sys/types.h>
#include "global_data.h"

LoginType login_type;       // 登录类型：管理员，普通用户，游客

int sfd;                    // socket file descripter

User *user_list;            // 所有用户的链表，为无头尾结点的单链表

bool connected;             // 是否连接上了服务器/客户端
