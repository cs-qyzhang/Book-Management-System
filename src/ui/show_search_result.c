/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : show_search_result.c
 * author      : qiuyang Zhang
 * created     : 2018/10/21
 * description : 
 *
 */
#include <gtk/gtk.h>
#include "../data-structure/book_search.h"

int
show_search_result(BookSearch **book, int record_num, GtkWidget *vbox)
{
    if (record_num <= 0)
        return 0;


    GtkWidget *image_book;
    GtkWidget *button_booking, *image_booking;
    GtkWidget *button_title, *label_author, *label_publisher, *label_detail;
    GtkWidget *hbox, *vbox_label;

    gtk_box_set_homogeneous(GTK_BOX(vbox), FALSE);

    int i;
    for (i = 0; i < record_num; ++i)
    {
        button_booking = gtk_button_new();
        image_booking = gtk_image_new_from_file("../resources/image/book_booking.gif");
        gtk_button_set_image(GTK_BUTTON(button_booking), image_booking);

        button_title = gtk_button_new_with_label(book[i]->bs_title);
        gtk_widget_set_halign(button_title, GTK_ALIGN_START);

        label_author = gtk_label_new(book[i]->bs_author);
        label_publisher = gtk_label_new(book[i]->bs_publisher);
        label_detail = gtk_label_new(book[i]->bs_detail);
        gtk_label_set_line_wrap(GTK_LABEL(label_author), TRUE);
        gtk_label_set_line_wrap(GTK_LABEL(label_publisher), TRUE);
        gtk_label_set_line_wrap(GTK_LABEL(label_detail), TRUE);
        gtk_label_set_xalign(GTK_LABEL(label_author), 0);
        gtk_label_set_xalign(GTK_LABEL(label_publisher), 0);
        gtk_label_set_xalign(GTK_LABEL(label_detail), 0);

        gtk_widget_set_size_request(label_author, 150, -1);
        gtk_widget_set_size_request(label_publisher, 150, -1);
        gtk_widget_set_size_request(label_detail, 150, -1);


        vbox_label = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
        gtk_box_pack_start(GTK_BOX(vbox_label), button_title, FALSE, TRUE, 5);
        gtk_box_pack_start(GTK_BOX(vbox_label), label_author, FALSE, TRUE, 5);
        gtk_box_pack_start(GTK_BOX(vbox_label), label_publisher, FALSE, TRUE, 5);
        gtk_box_pack_start(GTK_BOX(vbox_label), label_detail, FALSE, TRUE, 5);
        gtk_box_set_homogeneous(GTK_BOX(vbox_label), FALSE);

        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_box_pack_start(GTK_BOX(hbox), button_booking, FALSE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), vbox_label, FALSE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 0);
    }

    return record_num;
}

