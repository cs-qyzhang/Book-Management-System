/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : search_user.c
 * author      : qiuyang Zhang
 * created     : 2018/10/22
 * description : 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./search_user.h"
#include "../global_data.h"

/*
 * 函数名称：search_user
 * 函数功能：在用户链表中查找是否有该用户
 * 函数输入：User *user_search : 要查找的用户
 * 函数输出：User *, 该用户在用户链表中的指针，若没有该用户则返回NULL
 * 函数说明：用户链表为无头结点尾结点的单链表；若用户为root则允许使用
 *           普通用户身份登录
 * 创建时间：2018/10/22
 *
 */
User *
search_user(User *user_search)
{
    User *p;
    p = user_list;
    
    if (user_search->job_id != NULL)
    {
        while (p != NULL)
        {
            if (!strcmp(p->job_id, user_search->job_id)
                && !strcmp(p->password, user_search->password))
            {
                if (p->root == true || p->root == user_search->root)
                    return p;
                else
                    return NULL;
            }
            p = p->next;
        }
    }
    else
    {
        while (p != NULL)
        {
            if (!strcmp(p->username, user_search->username)
                && !strcmp(p->password, user_search->password))
            {
                if (p->root == true || p->root == user_search->root)
                    return p;
                else
                    return NULL;
            }
            p = p->next;
        }
    }

    return NULL;
}

