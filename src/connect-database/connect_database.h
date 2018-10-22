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
#include "../data-structure/book_search.h"

#define PORT_SERVER "1222"          // 服务器监听端口
#define IP_SERVER   "120.78.79.23"  // 服务器ip地址
//#define IP_SERVER   "172.16.31.61"   服务器ip地址
//#define IP_SERVER   "127.0.0.1"   // 服务器ip地址
#define VALUE_NAME_LEN  50          // 键值对中键字符串的最大长度
#define VALUE_LEN   100             // 键值对中值字符串的最大长度

bool connect_to_server();
bool close_connection_to_server();
bool listen_to_client();

bool connect_to_library(const char url[], const char filename[]);

char* value_type(const char *value_name);
char* value_write(const char *value_name, const void *value);
bool value_read(const char *source, char *value_name, void *value);

int parse_search_html(const char *filename, BookSearch *result[]);

bool send_value(const char *value_name, const void *value);
bool send_line(const char *msg);

#endif // CONNECT_DATABASE_H
