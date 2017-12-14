/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <sys/unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../Types/MyDataTypes.h"
#include "geTime.h"

void delay_us(__useconds_t t_delay)
{
    usleep(t_delay);
}

void delay_ms(__useconds_t t_delay)
{
    usleep(1000 * t_delay);
}

void delay_s(__useconds_t t_delay)
{
    usleep(1000000 * t_delay);
}

s8 get_date_time(char * date_time)
{
    s8 res = 0;
    if (16 < strlen(date_time))
    {
        res = FAILURE;
    }
    else
    {
        time_t rawtime;
        time(&rawtime);
        struct tm *timeinfo = localtime(&rawtime);
        sprintf(date_time, "%d%d%d%d%d%d\n", timeinfo->tm_year + 1900,
                timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour,
                timeinfo->tm_min, timeinfo->tm_sec);
        
        res = SUCCESS;
    }
    return (res);
}