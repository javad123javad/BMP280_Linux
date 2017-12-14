/** @file sqldriver.h
 * @brief This Module contains required function to store/obtain data from
 * sqlite data-base
 * @author Javad Rahimi
 *  
 */

#include "sqlite3.h"

#include "../MyLib/Types/MyDataTypes.h"
#include "../Sensors/BME280/bmp280_impl.h"
#include "sqldriver.h"

#define DEBUG_EN
static s8 g_db_init = FAILURE;

static s8 callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    NotUsed = 0;

    for (int i = 0; i < argc; i++)
    {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

s8 db_init(sqlite3 ** db, const char * db_name)
{
    s8 res = 0;
    s8 db_response = 0;
    db_response = sqlite3_open(db_name, db);
    if (SQLITE_OK == db_response)
    {
        res = SUCCESS;
        g_db_init = SUCCESS;
    }
    else
    {
#ifdef DEBUG_EN
        fprintf(stderr, "Init Error: %s", sqlite3_errmsg(db));
#endif
        res = FAILURE;
    }
    sqlite3_close(db);
    return (res);
}

s8 db_create(sqlite3 * db, const char * table_name)
{
    s8 res = 0;
    s8 db_resp = 0;
    char db_query[2048] = {0};
    char *errmsg;
    sqlite3_stmt * stmt; /* 1 */

    if (SUCCESS != g_db_init)
    {
        return FAILURE;
    }
    if (NULL == table_name)
    {
        sprintf(db_query, "CREATE TABLE BME280 ( "\
                    "date_time  TEXT PRIMARY KEY,"\
                    "hum       TEXT ,"\
                    "temp        TEXT ,"\
                    "press      TEXT "\
                    ");", table_name);
    }
    else
    {
        sprintf(db_query, "CREATE TABLE %s ( "\
                    "date_time  TEXT PRIMARY KEY,"\
                    "hum       TEXT ,"\
                    "temp        TEXT ,"\
                    "press      TEXT "\
                    ");", table_name);
    }
    puts(db_query);
    sqlite3_prepare_v2(db, db_query, -1, &stmt, NULL); /* 2 */
    db_resp = sqlite3_step(stmt);

    if (SQLITE_DONE == db_resp)
    {
        res = SUCCESS;
        puts("I'm ok");
        sqlite3_finalize(stmt); /* 4 */
    }
    else
    {
#ifdef DEBUG_EN

        fprintf(stderr, "Write Error: %s", sqlite3_errmsg(db));
#endif
        res = FAILURE;

    }

}

s8 db_read(sqlite3 * db, struct bme_data * data)
{
    s8 res = 0;
    s8 db_resp = 0;
    char * err_msg;
    if (SUCCESS == g_db_init)
    {
        char *sql = "SELECT * FROM BME280";

        db_resp = sqlite3_exec(db, sql, callback, 0, &err_msg);

        if (SQLITE_OK != db_resp)
        {
            return FAILURE;
        }



    }
    else
    {
#ifdef DEBUG_EN
        fprintf(stderr, "Init Error: %s", sqlite3_errmsg(db));
#endif
        res = FAILURE;
    }

    return (res);
}

s8 db_write(sqlite3 * db, const char * table_name, const struct bme_data * data)
{
    s8 res = 0;
    s8 db_resp = 0;
    char db_query[2048] = {0};
    char *errmsg;
    sqlite3_stmt * stmt; /* 1 */

    if (SUCCESS == g_db_init)
    {
        if (NULL == data)
        {
            return FAILURE;
        }
        if(NULL == table_name)
        {
        sprintf(db_query, "insert into BME280 (date_time, hum, temp, press)"
                " values (%s, %s, %s, %s);", data->date_time, data->humidity,
                data->pressure, data->temp);
        }
        else
        {
            sprintf(db_query, "insert into %s (date_time, hum, temp, press)"
                " values (%s, %s, %s, %s);", table_name, data->date_time,
                    data->humidity, data->pressure, data->temp);
        }
        puts(db_query);
        sqlite3_prepare_v2(db, db_query, -1, &stmt, NULL); /* 2 */
        db_resp = sqlite3_step(stmt);
#if 0 
        db_resp = sqlite3_exec(db, "CREATE TABLE demo (name TEXT, age INTEGER);",
                               callback, NULL, &errmsg);
#endif
        if (SQLITE_DONE == db_resp)
        {
            res = SUCCESS;
            sqlite3_finalize(stmt); /* 4 */
        }
        else
        {
#ifdef DEBUG_EN

            fprintf(stderr, "Write Error: %s", sqlite3_errmsg(db));
#endif
            res = FAILURE;

        }

    }
    else
    {
#ifdef DEBUG_EN
        fprintf(stderr, "Init Error in Write: %s", sqlite3_errmsg(db));
#endif
        res = FAILURE;
    }

    return (res);
}
