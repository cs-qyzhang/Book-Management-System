/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : user.h
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 用户结构
 *
 */
#ifndef USER_H
#define USER_H

#include <stdbool.h>
#include "borrow_book.h"

typedef struct user
{
    char *username;             // 用户名
    char *password;             // 用户密码
    bool root;                  // 是否是管理员
    char *job_id;               // 工号
    BorrowBook *borrow_book;    // 已借阅的图书 单链表头指针
    BorrowBook *borrow_history; // 借阅历史 单链表头指针
    struct user *next;          // 指向链表下一个节点

}User;

#endif // USER_H
