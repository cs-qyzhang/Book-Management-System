/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : global_data.h
 * author      : qiuyang Zhang
 * created     : 2018/10/18
 * description : 全局变量头文件
 *
 */
#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>

/*
 * 登录类型枚举
 */
typedef enum login_type
{
    LOGIN_TYPE_ROOT,    // 管理员
    LOGIN_TYPE_USER,    // 普通用户
    LOGIN_TYPE_NONE     // 游客
}LoginType;

bool login_type_root();
bool login_type_user();
bool login_type_none();

#endif // GLOBAL_DATA_H
