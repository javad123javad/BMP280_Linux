/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bmp280_impl.h
 * Author: javad
 *
 * Created on August 5, 2017, 2:41 PM
 */

#ifndef BMP280_IMPL_H
#define BMP280_IMPL_H
#include "bme280.h"
#include "bme280_defs.h"
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

typedef struct bme_data
{
    char date_time[16];
    char temp[20];
    char pressure[20];
    char humidity[20];
};
typedef struct bme_data bme_data1;
void print_sensor_data(struct bme280_data *comp_data);
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev, 
        struct bme_data * bme_out);

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev,
        struct bme_data * bme_out);



#endif /* BMP280_IMPL_H */

