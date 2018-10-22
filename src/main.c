/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : main.c
 * author      : qiuyang Zhang
 * created     : 2018/10/21
 * description : 主函数
 *
 */
#include <gtk/gtk.h>
#include "./ui/gtk_callback_function.h"
#include "./global_data.h"

int
main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    
    GtkWidget *window;
    GtkWidget *hpaned;
    GtkWidget *scrolled_window_left, *scrolled_window_right;
    GtkWidget *frame_user, *frame_search, *frame_manage, *frame_info,
              *frame_statistic;
    GtkWidget *vbox_scrolled_window_left, *vbox_frame_user, *vbox_frame_manage,
              *vbox_frame_info, *vbox_frame_search, *vbox_frame_statistic;
    GtkWidget *toggle_button_search_normal, *toggle_button_search_complex,
              *toggle_button_info_main,
              *toggle_button_info_announcement, *toggle_button_info_navigation,
              *toggle_button_manage_add, *toggle_button_manage_delete,
              *toggle_button_manage_change, *toggle_button_statistic_login,
              *toggle_button_statistic_search;
    GtkWidget *button_user_login;
    GtkWidget *label_frame_user_connection_state, *label_frame_user_current_user;

    label_frame_user_connection_state = gtk_label_new("连接状态：离线");
    label_frame_user_current_user = gtk_label_new("当前用户：游客");

    toggle_button_info_main = gtk_toggle_button_new_with_label("主页");
    toggle_button_info_announcement = gtk_toggle_button_new_with_label("公告");
    toggle_button_info_navigation = gtk_toggle_button_new_with_label("馆内导航");
    toggle_button_search_normal = gtk_toggle_button_new_with_label("常规检索");
    toggle_button_search_complex = gtk_toggle_button_new_with_label("高级检索");
    toggle_button_manage_add = gtk_toggle_button_new_with_label("添加记录");
    toggle_button_manage_change = gtk_toggle_button_new_with_label("修改记录");
    toggle_button_manage_delete = gtk_toggle_button_new_with_label("删除记录");
    toggle_button_statistic_login = gtk_toggle_button_new_with_label("登录数据统计");
    toggle_button_statistic_search = gtk_toggle_button_new_with_label("搜索数据统计");

    button_user_login = gtk_button_new_with_label("登录");

    vbox_frame_user = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    vbox_frame_info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    vbox_frame_search = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    vbox_frame_manage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    vbox_frame_statistic= gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);

    gtk_box_pack_start(GTK_BOX(vbox_frame_user), label_frame_user_connection_state, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_user), label_frame_user_current_user, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_user), button_user_login, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_info), toggle_button_info_main, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_info), toggle_button_info_announcement, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_search), toggle_button_search_normal, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_search), toggle_button_search_complex, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_manage), toggle_button_manage_add, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_manage), toggle_button_manage_change, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_manage), toggle_button_manage_delete, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_statistic), toggle_button_statistic_login, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_frame_statistic), toggle_button_statistic_search, FALSE, TRUE, 0);

    frame_user = gtk_frame_new("用户");
    frame_search = gtk_frame_new("检索");
    frame_info = gtk_frame_new("信息");
    frame_manage = gtk_frame_new("管理");
    frame_statistic = gtk_frame_new("数据统计");

    gtk_container_add(GTK_CONTAINER(frame_user), vbox_frame_user);
    gtk_container_add(GTK_CONTAINER(frame_info), vbox_frame_info);
    gtk_container_add(GTK_CONTAINER(frame_search), vbox_frame_search);
    gtk_container_add(GTK_CONTAINER(frame_manage), vbox_frame_manage);
    gtk_container_add(GTK_CONTAINER(frame_statistic), vbox_frame_statistic);

    vbox_scrolled_window_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox_scrolled_window_left), frame_user, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_scrolled_window_left), frame_info, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_scrolled_window_left), frame_search, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_scrolled_window_left), frame_statistic, FALSE, TRUE, 0);



    // 右边界面初始化
    GtkWidget *stack;
    GtkWidget *label_info_main_welcome, *label_info_announcement_welcome;

    // 普通检索界面
    GtkWidget *vbox_search_normal;
    GtkWidget *hbox_search_normal;
    GtkWidget *image_search_normal;
    GdkPixbuf *image_search_normal_pixbuf;
    GtkWidget *button_search_normal;
    GtkWidget *combo_box_text_search_normal;
    GtkWidget *entry_search_normal;

    button_search_normal = gtk_button_new_with_label("检索");
    image_search_normal_pixbuf = gdk_pixbuf_new_from_file_at_scale("../resources/image/search_normal.jpg",
                                                                    300, 200, TRUE, NULL);
    image_search_normal = gtk_image_new_from_pixbuf(image_search_normal_pixbuf);
    g_object_unref(image_search_normal_pixbuf);

    combo_box_text_search_normal = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box_text_search_normal), "关键字");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box_text_search_normal), "书刊名");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box_text_search_normal), "作者");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box_text_search_normal), "索书号");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box_text_search_normal), "主题");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box_text_search_normal), "ISBN");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_search_normal), 0);
    
    entry_search_normal = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_search_normal), MAX_ENTRY_LEN);
    
    gtk_widget_set_margin_top(image_search_normal, 90);
    gtk_widget_set_margin_start(combo_box_text_search_normal, 30);
    gtk_widget_set_margin_end(button_search_normal, 30);

    hbox_search_normal = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(hbox_search_normal), combo_box_text_search_normal, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_search_normal), entry_search_normal, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_search_normal), button_search_normal, FALSE, TRUE, 0);

    vbox_search_normal = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_pack_start(GTK_BOX(vbox_search_normal), image_search_normal, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_search_normal), hbox_search_normal, FALSE, FALSE, 0);

    /*
     * 检索结果
     */
    GtkWidget *vbox_search_result;

    vbox_search_result = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gpointer search_normal_data[3];
    search_normal_data[0] = combo_box_text_search_normal;
    search_normal_data[1] = entry_search_normal;
    search_normal_data[2] = vbox_search_result;

    g_signal_connect(G_OBJECT(button_search_normal), "clicked",
                              G_CALLBACK(cb_button_search_normal_clicked), search_normal_data);

    gtk_box_pack_start(GTK_BOX(vbox_search_normal), vbox_search_result, FALSE, TRUE, 0);


    //
    stack = gtk_stack_new();

    label_info_main_welcome = gtk_label_new("欢迎使用华中科技大学图书检索系统！");
    label_info_announcement_welcome = gtk_label_new("暂无公告！");
    gtk_stack_add_named(GTK_STACK(stack), label_info_main_welcome, "info_main");
    gtk_stack_add_named(GTK_STACK(stack), label_info_announcement_welcome, "info_announcement");
    gtk_stack_add_named(GTK_STACK(stack), vbox_search_normal, "search_normal");

    gtk_stack_set_homogeneous(GTK_STACK(stack), FALSE); // 使stack中不同的子部件拥有的大小不同

    scrolled_window_left = gtk_scrolled_window_new(NULL, NULL);
    scrolled_window_right = gtk_scrolled_window_new(NULL, NULL);

    gtk_container_add(GTK_CONTAINER(scrolled_window_left), vbox_scrolled_window_left);
    gtk_container_add(GTK_CONTAINER(scrolled_window_right), stack);
    /*gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_window_left), 200);*/
    /*gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_window_right), 500);*/
    /*gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window_left), 500);*/
    /*gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window_right), 500);*/

    hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_paned_add1(GTK_PANED(hpaned), scrolled_window_left);
    gtk_paned_add2(GTK_PANED(hpaned), scrolled_window_right);
    gtk_paned_set_position(GTK_PANED(hpaned), 200);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "华中科技大学图书检索系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 750, 550);
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    gtk_container_add(GTK_CONTAINER(window), hpaned);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button_user_login), "clicked", G_CALLBACK(cb_button_login_clicked), window);


    GtkWidget *cb_toggle_button_toggled_data[9][2];
    int i;
    for (i = 0; i < 9; ++i)
        cb_toggle_button_toggled_data[i][0] = stack;

    cb_toggle_button_toggled_data[0][1] = label_info_main_welcome;
    cb_toggle_button_toggled_data[1][1] = label_info_announcement_welcome;
    cb_toggle_button_toggled_data[2][1] = vbox_search_normal;
    cb_toggle_button_toggled_data[3][1] = label_info_main_welcome;
    cb_toggle_button_toggled_data[4][1] = label_info_main_welcome;
    cb_toggle_button_toggled_data[5][1] = label_info_main_welcome;
    cb_toggle_button_toggled_data[6][1] = label_info_main_welcome;
    cb_toggle_button_toggled_data[7][1] = label_info_main_welcome;
    cb_toggle_button_toggled_data[8][1] = label_info_main_welcome;

    g_signal_connect(G_OBJECT(toggle_button_info_main), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[0]);
    g_signal_connect(G_OBJECT(toggle_button_info_announcement), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[1]);
    g_signal_connect(G_OBJECT(toggle_button_search_normal), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[2]);
    g_signal_connect(G_OBJECT(toggle_button_search_complex), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[3]);
    g_signal_connect(G_OBJECT(toggle_button_manage_add), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[4]);
    g_signal_connect(G_OBJECT(toggle_button_manage_change), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[5]);
    g_signal_connect(G_OBJECT(toggle_button_manage_delete), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[6]);
    g_signal_connect(G_OBJECT(toggle_button_statistic_login), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[7]);
    g_signal_connect(G_OBJECT(toggle_button_statistic_search), "toggled", G_CALLBACK(cb_toggle_button_toggled), cb_toggle_button_toggled_data[8]);

    // 程序初始化
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_button_info_main), TRUE);
    gtk_widget_show_all(window);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "info_main");

    gtk_main();
    return 0;
}

