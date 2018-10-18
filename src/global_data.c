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

bool login_type_root()
{
    return (login_type == LOGIN_TYPE_ROOT) ? true : false;
}

bool login_type_user()
{
    return (login_type == LOGIN_TYPE_USER) ? true : false;
}

bool login_type_none()
{
    return (login_type == LOGIN_TYPE_NONE) ? true : false;
}
