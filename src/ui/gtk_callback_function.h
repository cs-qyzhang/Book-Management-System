/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : gtk_callback_function.h
 * author      : qiuyang Zhang
 * created     : 2018/10/21
 * description : 
 *
 */
#ifndef GTK_CALLBACK_FUNCTION_H
#define GTK_CALLBACK_FUNCTION_H

#include <gtk/gtktypes.h>
#include <glib/gtypes.h>

void cb_toggle_button_toggled(GtkWidget *, GtkWidget *data[2]);
void cb_button_search_normal_clicked(GtkWidget *button, GtkWidget **data);
void cb_button_login_clicked(GtkWidget *button, GtkWindow *window);

#endif // GTK_CALLBACK_FUNCTION_H
