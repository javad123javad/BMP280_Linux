/** @file sqldriver.h
 * @brief This Module contains required function to store/obtain data from
 * sqlite data-base
 * @author Javad Rahimi
 *  
 */

#ifndef _SQLDRIVER_H
#define _SQLDRIVER_H
#include "sqlite3.h"
#ifdef __cplusplus
extern "C" {
#endif
#define CREATE_DB "CREATE TABLE BME280 ( "\
                    "date_time  TEXT PRIMARY KEY,"\
                    "hum       TEXT ,"\
                    "temp        TEXT ,"\
                    "press      TEXT "\
                    ");"
     
#define READ_DATA "select * from BME280"
    
    s8 db_init(sqlite3 ** db, const char * db_name);
    s8 db_create(sqlite3 * db, const char * table_name);
    s8 db_read(sqlite3 * db, struct bme_data * data);
    s8 db_write(sqlite3 * db, const char * table_name,
            const struct bme_data * data);
    
    
#ifdef __cplusplus
}
#endif
#endif /* _SQLDRIVER_H */