/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : login.h
 * author      : qiuyang Zhang
 * created     : 2018/10/22
 * description : 
 *
 */
#ifndef LOGIN_H
#define LOGIN_H

#include "../data-structure/user.h"

void login_authentication();
bool login_request(User *user_info);

#endif // LOGIN_H
