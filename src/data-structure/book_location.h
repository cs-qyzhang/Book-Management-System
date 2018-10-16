/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : book_location.h
 * author      : qiuyang Zhang
 * created     : 2018/10/16
 * description : 书籍馆藏位置结构
 *
 */
#ifndef BOOK_LOCATION_H
#define BOOK_LOCATION_H

typedef enum library
{
    LIBRARY_MAIN,       // 主校区图书馆
    LIBRARY_EAST        // 东校区图书馆

}Library;

typedef enum area
{
    AREA_A,             // A 区
    AREA_B,             // B 区
    AREA_C,             // C 区
    AREA_D              // D 区
}Area;

typedef struct book_location
{
    Library library;    // 图书馆
    Area area;          // 区域
    int floor;          // 楼层

}BookLocation;

#endif // BOOK_LOCATION_H
