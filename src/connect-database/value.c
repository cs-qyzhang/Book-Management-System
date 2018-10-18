/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : value.c
 * author      : qiuyang Zhang
 * created     : 2018/10/18
 * description : 键值对操作函数
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "connect_database.h"

/*
 * 函数名称：value_type
 * 函数功能：根据键值对的键得到值的类型
 * 函数输入：const char *value_name : 键
 * 函数输出：char *, 值的类型
 * 函数说明：值的类型：
 *              int,
 *              double,
 *              string
 * 创建时间：2018/10/18
 *
 */
char *
value_type(const char *value_name)
{
    char *result = NULL;
    if (!strcmp(value_name, "username"))
    {
        result = (char *)malloc(strlen("string") * sizeof(char) + 1);
        strcpy(result, "string");
    }
    else if (!strcmp(value_name, "password"))
    {
        result = (char *)malloc(strlen("string") * sizeof(char) + 1);
        strcpy(result, "string");
    }
    else
        ;

    return result;
}

/*
 * 函数名称：value_to_string
 * 函数功能：将键值对中的值转换为字符串
 * 函数输入：const char *value_name : 键值对中的键
 *           void *value            : 键值对中的值
 * 函数输出：char *, 值字符串
 * 函数说明：无
 * 创建时间：2018/10/18
 *
 */
char *
value_to_string(const char *value_name, const void *value)
{
    char *result = NULL;
    char *type = NULL;
    char temp[VALUE_LEN + 1];
    type = value_type(value_name);
    if (!strcmp(type, "int"))
        sprintf(temp, "%d", *(int *)value);
    else if (!strcmp(type, "double"))
        sprintf(temp, "%lf", *(double *)value);
    else if (!strcmp(type, "string"))
        sprintf(temp, "%s", (char *)value);
    else
        ;

    result = (char *)malloc(strlen(temp) * sizeof(char) + 1);
    strcpy(result, temp);
    free(type);
    return result;
}

/*
 * 函数名称：string_to_value
 * 函数功能：将字符串类型的值转换为键值对中值的类型数据
 * 函数输入：const char *value_name : 键值对中的键
 *           char *value_string     : 字符串表示的键值对中的值
 * 函数输出：void *, 键值对中的值
 * 函数说明：无
 * 创建时间：2018/10/18
 *
 */
void *
string_to_value(char *value_name, char *value_string)
{
    char *type = NULL;
    void *result = NULL;

    type = value_type(value_name);
    if (!strcmp(type, "int"))
    {
        result = (int *)malloc(sizeof(int));
        sscanf(value_string, "%d", (int *)result);
    }
    else if (!strcmp(type, "double"))
    {
        result = (double *)malloc(sizeof(double));
        sscanf(value_string, "%lf", (double *)result);
    }
    else if (!strcmp(type, "string"))
    {
        result = (char *)malloc(strlen(value_string) * sizeof(char) + 1);
        strcpy((char *)result, value_string);
    }
    else
        ;

    free(type);
    return result;
}

/*
 * 函数名称：value_write
 * 函数功能：根据键值对的键和键值对的值将该键值对转换为一行字符串
 * 函数输入：const char *value_name : 键值对的键
 *           cosnt void *value      : 键值对的值
 * 函数输出：char *, 转换为的一行字符串
 * 函数说明：无
 * 创建时间：2018/10/18
 *
 */
char *
value_write(const char *value_name, const void *value)
{
    char *result = NULL;
    char *value_string = NULL;
    char temp[VALUE_LEN + VALUE_NAME_LEN + 3];

    value_string = value_to_string(value_name, value);
    sprintf(temp, "%s: %s", value_name, value_string);
    result = (char *)malloc(strlen(temp) * sizeof(char) + 1);
    strcpy(result, temp);
    free(value_string);

    return result;
}

/*
 * 函数名称：value_read
 * 函数功能：从一行字符串中读取键值对
 * 函数输入：const char *source : 源字符串
 * 函数输出：char *value_name   : 得到的键值对的键
 *           void *value        : 得到的键值对的值
 * 函数说明：无
 * 创建时间：2018/10/18
 *
 */
bool
value_read(const char *source, char *value_name, void *value)
{
    char value_name_temp[VALUE_NAME_LEN + 1];
    char value_temp[VALUE_LEN + 1];

    sscanf(source, "%s %s", value_name_temp, value_temp);
    value_name_temp[strlen(value_name_temp) - 1] = '\0';

    value_name = (char *)malloc(strlen(value_name_temp) * sizeof(char) + 1);
    strcpy(value_name, value_name_temp);
    value = string_to_value(value_name_temp, value_temp);

    return true;
}
