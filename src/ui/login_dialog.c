/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : login_dialog.c
 * author      : qiuyang Zhang
 * created     : 2018/10/22
 * description : 
 *
 */
#include <gtk/gtk.h>
#include <stdbool.h>
#include "../data-structure/user.h"
#include "../connect-database/connect_database.h"
#include "../login/login.h"

bool
login_dialog(GtkWindow *parent)
{
    GtkWidget *login_dialog;
    GtkWidget *label_username, *label_job_id, *label_username_password,
              *label_username_root, *label_job_id_password, *label_job_id_root;
    GtkWidget *checkbutton_username_root, *checkbutton_job_id_root;
    GtkWidget *entry_username, *entry_job_id,
              *entry_username_password, *entry_job_id_password;
    GtkWidget *stack, *stack_switcher;
    GtkWidget *hbox_username, *hbox_job_id, *hbox_username_password,
              *hbox_job_id_password, *hbox_username_root, *hbox_job_id_root;
    GtkWidget *vbox_username, *vbox_job_id, *vbox_content_area;
    GtkWidget *dialog_content_area;

    login_dialog = gtk_dialog_new_with_buttons("用户登录", parent, GTK_DIALOG_MODAL,
                        "登录", GTK_RESPONSE_OK, "取消", GTK_RESPONSE_NO, NULL);

    label_username          = gtk_label_new("用户名：");
    label_job_id            = gtk_label_new("学工号：");
    label_job_id_password   = gtk_label_new("密　码：");
    label_username_password = gtk_label_new("密　码：");
    label_job_id_root       = gtk_label_new("管理员？");
    label_username_root     = gtk_label_new("管理员？");

    checkbutton_username_root = gtk_check_button_new();
    checkbutton_job_id_root   = gtk_check_button_new();
    entry_job_id              = gtk_entry_new();
    entry_username            = gtk_entry_new();
    entry_username_password   = gtk_entry_new();
    entry_job_id_password     = gtk_entry_new();

    stack             = gtk_stack_new();
    stack_switcher    = gtk_stack_switcher_new();
    vbox_username = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    vbox_job_id   = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    hbox_job_id            = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    hbox_username          = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    hbox_username_password = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    hbox_job_id_password   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    hbox_username_root     = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    hbox_job_id_root       = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    gtk_box_pack_start(GTK_BOX(hbox_job_id), label_job_id, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_job_id), entry_job_id, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_username), label_username, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_username), entry_username, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_username_password), label_username_password, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_username_password), entry_username_password, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_job_id_password), label_job_id_password, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_job_id_password), entry_job_id_password, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_username_root), label_username_root, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_username_root), checkbutton_username_root, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_job_id_root), label_job_id_root, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_job_id_root), checkbutton_job_id_root, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vbox_username), hbox_username, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_username), hbox_username_password, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_username), hbox_username_root, FALSE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(vbox_job_id), hbox_job_id, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_job_id), hbox_job_id_password, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_job_id), hbox_job_id_root, FALSE, TRUE, 0);

    gtk_stack_add_titled(GTK_STACK(stack), vbox_username, "username", "按用户名登录");
    gtk_stack_add_titled(GTK_STACK(stack), vbox_job_id, "job_id", "按学工号登录");

    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switcher), GTK_STACK(stack));

    vbox_content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox_content_area), stack_switcher, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_content_area), stack, TRUE, TRUE, 0);

    dialog_content_area = gtk_dialog_get_content_area(GTK_DIALOG(login_dialog));
    gtk_container_add(GTK_CONTAINER(dialog_content_area), vbox_content_area);
    gtk_widget_show_all(login_dialog);

    gint result;
    result = gtk_dialog_run(GTK_DIALOG(login_dialog));

    User user_login;

    switch (result)
    {
        case GTK_RESPONSE_OK:
            if (gtk_stack_get_visible_child(GTK_STACK(stack)) == vbox_username)
            {
                user_login.username = (char *)malloc(strlen(gtk_entry_get_text(GTK_ENTRY(entry_username))) + 1);
                strcpy(user_login.username, gtk_entry_get_text(GTK_ENTRY(entry_username)));
                user_login.job_id = NULL;
                user_login.password = (char *)malloc(strlen(gtk_entry_get_text(GTK_ENTRY(entry_username_password))) + 1);
                strcpy(user_login.username, gtk_entry_get_text(GTK_ENTRY(entry_username_password)));
                user_login.root = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton_username_root));
            }
            else
            {
                user_login.job_id = (char *)malloc(strlen(gtk_entry_get_text(GTK_ENTRY(entry_job_id))) + 1);
                strcpy(user_login.username, gtk_entry_get_text(GTK_ENTRY(entry_job_id)));
                user_login.username = NULL;
                user_login.password = (char *)malloc(strlen(gtk_entry_get_text(GTK_ENTRY(entry_job_id_password))) + 1);
                strcpy(user_login.username, gtk_entry_get_text(GTK_ENTRY(entry_job_id_password)));
                user_login.root = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton_job_id_root));
            }
            if (login_request(&user_login))
            {
                g_print("登录成功！");
            }
            else
            {
                g_print("登录失败！");
            }
            break;
        case GTK_RESPONSE_NO:
            break;
        case GTK_RESPONSE_DELETE_EVENT:
            break;
        default:
            break;
    }
    gtk_widget_destroy(login_dialog);
    return false;
}

