/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestBench.h
 * Author: javad
 * 
 * Created on August 5, 2017, 4:11 PM
 * This file contains required function headers for the sensor testers 
 */

#ifndef TESTBENCH_H
#define TESTBENCH_H
#include "Sensors/BME280/bmp280_impl.h"

/* User Defined And Device Includes */

/* Functions Prototype*/
void Test_BME280(); /*< This Function tests BME280 Sensor */
void Test_WebServer(); /*< This Function tests Mongoose Embedded HTTP Server */ 
void Test_SQLite();

void Get_BME280_Data(struct bme_data * bme_out);
void   get_BME280_json_data(char * bme_json_out);

#endif /* TESTBENCH_H */

