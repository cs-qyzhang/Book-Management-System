/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : book_search.c
 * author      : qiuyang Zhang
 * created     : 2018/10/21
 * description : 图书查找函数
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./search_book.h"
#include "../connect-database/connect_database.h"

int
search_book_normal(BookSearch *result[], const char search_type, const char search_arg[])
{
    char url[301];
    int record_num;
    
    sprintf(url, "/search*chx/?searchtype=%c&searcharg=%s", search_type, search_arg);

    if (!connect_to_library(url, "/tmp/search_result_normal.html"))
        return -1;

    record_num = parse_search_html("/tmp/search_result_normal.html", result);
    if (record_num == -1)
        return -1;

    return record_num;
}

int
search_book_complex(BookSearch *result[], const char search_arg[])
{
    char url[301];
    
    sprintf(url, "/search*chx/?searchtype=X&searcharg=%s", search_arg);

    if (!connect_to_library(url, "/tmp/search_result_complex.html"))
        return -1;

    if (!parse_search_html("/tmp/search_result_complex.html", result))
        return -1;

    return true;
}
