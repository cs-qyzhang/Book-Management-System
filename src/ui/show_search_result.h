/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : show_search_result.h
 * author      : qiuyang Zhang
 * created     : 2018/10/21
 * description : 
 *
 */
#ifndef SHOW_SEARCH_RESULT_H
#define SHOW_SEARCH_RESULT_H
#include <gtk/gtktypes.h>
#include "../data-structure/book_search.h"

int show_search_result(BookSearch **book, int record_num, GtkWidget *vbox);

#endif // SHOW_SEARCH_RESULT_H
