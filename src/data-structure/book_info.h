/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : book_info.h
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 图书馆藏信息结构
 *
 */
#ifndef BOOK_INFO_H
#define BOOK_INFO_H

#include <time.h>
#include "book_location.h"

typedef enum book_state
{
    BOOK_STATE_HAVE,        // 在架上
    BOOK_STATE_INSIDE,      // 馆内阅览
    BOOK_STATE_BORROWED     // 已借阅

}BookState;

typedef struct book_info
{
    BookLocation *location; // 图书位置
    int amount;             // 图书数量
    BookState book_state;   // 馆藏状态
    struct tm *return_time; // 到期时间
    
}BookInfo;

#endif //BOOK_INFO_H
