/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : book_search.h
 * author      : qiuyang Zhang
 * created     : 2018/10/19
 * description : 存放查询网页中每一个图书的数据
 *
 */
#ifndef BOOK_SEARCH_H
#define BOOK_SEARCH_H

typedef struct book_search
{
    char *bs_title;
    char *bs_detail;
    char *bs_author;
    char *bs_publisher;
    char *bs_url;

}BookSearch;

#endif // BOOK_SEARCH_H
