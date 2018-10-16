/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : cnmarc.h
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : CNMARK-中国机读目录格式结构
 *
 */
#ifndef CNMARC_H
#define CNMARC_H

#include "publish_info.h"

typedef struct cn_marc
{
    // Time date;
    char *ISBN;             // 010  ISBN 号
    char *id;               // 090  索书号
    char *language;         // 101  语言
    char **title;           // 200  书名（包含作者信息）
    PublishInfo *publish;   // 210  出版信息
    char **form;            // 215  载体形式
    char **series;          // 225  系列
    char **abstract;        // 330  摘要
    char **author;          // 701  作者
    char **translator;      // 702  翻译者
    char **theme;           // 606  主题

}CNMARC;

#endif // CNMARC_H
