/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : book.h
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 图书结构
 *
 */
#ifndef BOOK_H
#define BOOK_H

#include "cnmarc.h"
#include "book_info.h"

typedef struct book
{
    CNMARC   *cnmarc;       // 图书的CNMARC信息
    BookInfo *book_info;    // 图书的馆藏信息

}Book;

#endif //BOOK_H
