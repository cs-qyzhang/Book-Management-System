/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : borrow_book.h
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 借阅图书结构
 *
 */
#ifndef BORROW_BOOK_H
#define BORROW_BOOK_H

#include <time.h>
#include "book_location.h"
#include "cnmarc.h"

typedef struct borrow_book
{
    struct tm *borrowed_time;       // 借阅时间
    struct tm *return_time;         // 应归还/归还 时间
    CNMARC *cnmarc;                 // 借阅书的CNMARC信息
    BookLocation *book_location;    // 书籍位置
    struct borrow_book *next;       // 指向下一个的指针

}BorrowBook;

#endif // BORROW_BOOK_H
