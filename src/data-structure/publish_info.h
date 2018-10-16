/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : publish_info.h
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 出版信息结构
 *
 */
#ifndef PUBLISH_INFO_H
#define PUBLISH_INFO_H

typedef struct publish_info
{
    int year;           // 发行年份
    char *publisher;    // 出版社
    char *location;     // 出版社所在地

}PublishInfo;

#endif // PUBLISH_INFO_H
