/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: javad
 *
 * Created on July 20, 2017, 4:55 PM
 */
#include <stdio.h>
#include <stdlib.h>

/* User defined Headers */
#include "TestBench.h"





int main(int argc, char** argv) {
    
    //Test_BME280();
   Test_WebServer();
   // Test_SQLite();
     // get_BME280_json_data();

    return (EXIT_SUCCESS);
}

