/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : parse_search_html_test.c
 * author      : qiuyang Zhang
 * created     : 2018/10/19
 * description : 测试parse_search_html
 *
 */
#include <stdio.h>
#include "connect_database.h"

int
main(void)
{
    char filename[] = "../search.html";
    BookSearch *book_search[BOOK_SEARCH_MAX];
    int book_num;
    book_num = parse_search_html(filename, book_search);

    int i;
    FILE *fp;
    fp = fopen("../book_search.txt", "w+");
    if (fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    for (i = 0; i < book_num; ++i)
    {
        fprintf(fp, "%d\n", i + 1);
        fprintf(fp, "title: %s\n", book_search[i]->bs_title);
        fprintf(fp, "author: %s\n", book_search[i]->bs_author);
        fprintf(fp, "publisher: %s\n", book_search[i]->bs_publisher);
        fprintf(fp, "detail: %s\n", book_search[i]->bs_detail);
        fprintf(fp, "url: %s\n\n", book_search[i]->bs_url);
    }
    fclose(fp);

    return 0;
}
