/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   geTime.h
 * Author: javad
 *
 * Created on August 5, 2017, 2:57 PM
 */

#ifndef GETIME_H
#define GETIME_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

void delay_us(__useconds_t t_delay);
void delay_ms(__useconds_t t_delay);
void delay_s(__useconds_t t_delay);

s8 get_date_time(char * date_time);

#endif /* GETIME_H */

