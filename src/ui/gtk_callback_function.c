/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : gtk_callback_function.c
 * author      : qiuyang Zhang
 * created     : 2018/10/21
 * description : 
 *
 */
#include <gtk/gtk.h>
#include "../search-book/search_book.h"
#include "./gtk_callback_function.h"
#include "./show_search_result.h"
#include "../ui/login_dialog.h"
#include "../global_data.h"

void cb_toggle_button_toggled(GtkWidget *toggle_button, GtkWidget *data[2])
{
    static GtkWidget *last_toggled_button = NULL;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button)))
    {
        if (last_toggled_button == NULL)
            last_toggled_button = toggle_button;
        else if (last_toggled_button == toggle_button)
            ;
        else
        {
            GtkWidget *temp;
            temp = last_toggled_button;
            last_toggled_button = toggle_button;
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(temp), FALSE);
            gtk_stack_set_visible_child(GTK_STACK(data[0]), data[1]);
        }
    }
    else
        if (toggle_button == last_toggled_button)
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_button), TRUE);
}

/*
 * 函数名称：cb_button_search_normal_clicked
 * 函数功能：常规检索按钮 回调函数
 * 函数输入：GtkWidget *button : 按钮
 *           GtkWidget **data  : 窗口部件数组，其中：
 *                  data[0]    : GtkComboBoxText, 搜索类型
 *                  data[1]    : GtkEntry, 搜索内容
 *                  data[2]    : GtkBox, 显示搜索结果的vbox
 * 函数输出：void
 * 函数说明：无
 * 创建时间：2018/10/21
 *
 */
void cb_button_search_normal_clicked(GtkWidget *button, GtkWidget **data)
{
    char search_type;
    char *combo_text;
    const char *search_arg = gtk_entry_get_text(GTK_ENTRY(data[1]));

    combo_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data[0]));
    if (!strcmp(combo_text, "关键字"))
        search_type = 'X';
    else if (!strcmp(combo_text, "书刊名"))
        search_type = 't';
    else if (!strcmp(combo_text, "作者"))
        search_type = 'a';
    else if (!strcmp(combo_text, "主题"))
        search_type = 'd';
    else if (!strcmp(combo_text, "索书号"))
        search_type = 'c';
    else if (!strcmp(combo_text, "ISBN"))
        search_type = 'i';
    else
        return;

    BookSearch *result[BOOK_SEARCH_MAX];
    int record_num;
    record_num = search_book_normal(result, search_type, search_arg);
    if (record_num == -1)
    {
        g_print("cb_button_search_normal_clicked : search_book_normal");
        return ;
    }

    char label_text[30];
    if (record_num == 0)
        sprintf(label_text, "没有查到记录！");
    else
        sprintf(label_text, "共找到 %d 条记录：", record_num);


    GtkWidget *label_record;
    label_record = gtk_label_new(label_text);
    gtk_label_set_xalign(GTK_LABEL(label_record), 0);
    gtk_box_pack_start(GTK_BOX(data[2]), label_record, FALSE, TRUE, 0);

    show_search_result(result, record_num, data[2]);
    gtk_widget_show_all(data[2]);
}

void cb_button_login_clicked(GtkWidget *button, GtkWindow *window)
{
    login_dialog(window);
}
