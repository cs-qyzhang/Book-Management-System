/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : book_search.h
 * author      : qiuyang Zhang
 * created     : 2018/10/21
 * description : 
 *
 */
#ifndef SEARCH_BOOK_H
#define SEARCH_BOOK_H

#include <stdbool.h>
#include "../data-structure/book_search.h"

int search_book_normal(BookSearch *result[], const char search_type, const char search_arg[]);
int search_book_complex(BookSearch *result[], const char search_arg[]);

#endif // SEARCH_BOOK_H
