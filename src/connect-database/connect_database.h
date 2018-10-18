/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : connect_database.h
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : TCP连接头文件
 *
 */
#ifndef CONNECT_DATABASE_H
#define CONNECT_DATABASE_H

#include <stdbool.h>
#include <sys/types.h>

#define PORT_SERVER 1222            // 服务器监听端口
#define IP_SERVER   "120.78.79.23"  // 服务器ip地址
//#define IP_SERVER   "127.0.0.1"  // 服务器ip地址
#define VALUE_NAME_LEN  50          // 键值对中键字符串的最大长度
#define VALUE_LEN   100             // 键值对中值字符串的最大长度

bool connect_to_server(char *send_msg, size_t send_len, char *recv_msg, size_t recv_len);
bool listen_to_client();

char* value_type(const char *value_name);
char* value_write(const char *value_name, const void *value);
bool vaule_read(const char *source, char *value_name, void *value);


#endif // CONNECT_DATABASE_H
