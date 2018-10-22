/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : parse_search_html.c
 * author      : qiuyang Zhang
 * created     : 2018/10/19
 * description : 解析搜索页面的html文件
 *
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./connect_database.h"
#include "../global_data.h"
#include "../data-structure/book_search.h"

int
fgetline(FILE *fp, char *buf, size_t buf_len)
{
    if (fp == NULL)
        return -1;

    int read_num = 0;
    char c;
    while ((c = fgetc(fp)))
    {
        if (c == '\0')
        {
            buf[read_num] = '\0';
            return read_num;
        }
        else if (c == '\r')
        {
            c = fgetc(fp);
            if (c == '\n')
            {
                buf[read_num] = '\0';
                return read_num;
            }
        }
        else if (c == '\n')
        {
            if (c == '\n')
            {
                buf[read_num] = '\0';
                return read_num;
            }
        }
        else
        {
            buf[read_num++] = c;
            if (read_num == (int)buf_len)
            {
                buf[read_num] = '\0';
                return read_num;
            }
        }
    }
    buf[read_num] = '\0';
    return read_num;
}

int
parse_search_html(const char *filename, BookSearch *result[])
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("parse_search_html : fopen");
        return -1;
    }

    char buf[1001];
    enum state
    {
        state_find_recode_num,
        state_find_title,
        state_wait_title,
        state_find_author,
        state_wait_author,
        state_find_publisher,
        state_wait_publisher,
        state_find_detail,
        state_wait_detail
    }state;

    state = state_find_recode_num;
    char *substr, *substr_end;
    char temp[50];
    int record_num = 0;
    int book_num = 0;
    while (fgetline(fp, buf, 1000) >= 0)
    {
        BookSearch *book_temp;
        switch (state)
        {
            case state_find_recode_num:
                if (strlen(buf) >= 100 && buf[0] == '<' && buf[1] == 'd'
                    && buf[6] == 'c' && buf[13] == 'b')
                {
                    substr = strstr(buf, "找到");
                    if (substr != NULL)
                    {
                        sscanf(substr, "%s%d", temp, &record_num);
                        if (record_num > BOOK_SEARCH_MAX)
                            record_num = BOOK_SEARCH_MAX;
                        state = state_find_title;
                    }
                }
                // 没有搜索到结果
                else if (buf[0] == '<' && buf[1] == 'b' && buf[2] == 'r' && buf[7] == 'h')
                    return 0;
                break;
            case state_find_title:
                if (buf[0] == '<' && buf[1] == 's'
                    && buf[6] == 'c' && buf[13] == 'b')
                {
                    substr = strstr(buf, "briefcitTitle");
                    if (substr != NULL)
                    {
                        state = state_wait_title;
                        book_temp = (BookSearch *)malloc(sizeof(BookSearch));
                    }
                }
                break;
            case state_wait_title:
                if (buf[0] == '<' && buf[1] == 'a' && buf[3] == 'h')
                {
                    substr = strchr(buf, '"');
                    ++substr;

                    substr_end = strchr(substr, '"');
                    book_temp->bs_url = (char *)malloc(substr_end - substr + 1);
                    strncpy(book_temp->bs_url, substr, substr_end - substr + 1);
                    book_temp->bs_url[substr_end - substr] = '\0';

                    substr = substr_end + 2;
                    substr_end = strchr(substr, '<');
                    book_temp->bs_title = (char *)malloc(substr_end - substr + 1);
                    strncpy(book_temp->bs_title, substr, substr_end - substr + 1);
                    book_temp->bs_title[substr_end - substr] = '\0';

                    state = state_find_author;
                }
                break;
            case state_find_author:
                if (buf[0] == '<' && buf[1] == 's'
                    && buf[6] == 'c' && buf[13] == 'b')
                {
                    substr = strstr(buf, "briefcitDetail");
                    if (substr != NULL)
                        state = state_wait_author;
                }
                break;
            case state_wait_author:
                book_temp->bs_author = (char *)malloc(strlen(buf) + 1);
                strcpy(book_temp->bs_author, buf);
                state = state_find_publisher;
                break;
            case state_find_publisher:
                if (buf[0] == '<' && buf[1] == 's'
                    && buf[6] == 'c' && buf[13] == 'b')
                {
                    substr = strstr(buf, "briefcitDetail");
                    if (substr != NULL)
                        state = state_wait_publisher;
                }
                break;
            case state_wait_publisher:
                book_temp->bs_publisher = (char *)malloc(strlen(buf) - 5);
                strncpy(book_temp->bs_publisher, buf, strlen(buf) - 6);
                book_temp->bs_publisher[strlen(buf) - 6] = '\0';
                state = state_find_detail;
                break;
            case state_find_detail:
                if (buf[0] == '<' && buf[1] == 's'
                    && buf[6] == 'c' && buf[13] == 'b')
                {
                    substr = strstr(buf, "briefcitDetail");
                    if (substr != NULL)
                        state = state_wait_detail;
                }
                break;
            case state_wait_detail:
                book_temp->bs_detail = (char *)malloc(strlen(buf) - 5);
                strncpy(book_temp->bs_detail, buf, strlen(buf) - 6);
                book_temp->bs_detail[strlen(buf) - 6] = '\0';
                
                result[book_num++] = book_temp;
                if (book_num == record_num)
                {
                    fclose(fp);
                    return book_num;
                }
                state = state_find_title;
                break;
            default:
                fclose(fp);
                return -1;
        }
    }
    fclose(fp);

    return book_num;
}
