/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Server/json.h"
#include "MyLib/I2C/I2CLib.h"
#include "Web_Server/mongoose.h"
#include "MyLib/GeFunctions/geTime.h"
#include "Sensors/BME280/bmp280_impl.h"
#include "sqlite/sqldriver.h"
#include "sqlite/sqlite3.h"
#include "TestBench.h"
static struct mg_serve_http_opts s_http_server_opts;

/********************************************************************/

void Test_BME280()
{
    struct bme280_dev dev;
    struct bme_data bme_out;
    s8 rslt = BME280_OK;
    u8 buf[2] = {0};

    dev.dev_id = BME280_I2C_ADDR_PRIM;
    dev.intf = BME280_I2C_INTF;
    dev.read = I2C_Read;
    dev.write = I2C_Write;
    dev.delay_ms = delay_ms;


    fprintf(stdout, "Start Testing BME280 via I2C Protocol...\n");

#if 0 
    if (I2C_SUCCESS == I2C_Init(1, 0x76))
    {
        printf("Protocol Configuration is Ok...\n");
        rslt = I2C_Read(0x76, 0xD0, buf, 1);
        printf("Data Read is %x\n", buf[0]);

    }
#endif
    if (I2C_SUCCESS != I2C_Init(I2C_BUS_1, BME280_I2C_ADDR_PRIM))
    {
        fprintf(stderr, "I2C Initialization Error On Device %x\n",
                BME280_I2C_ADDR_PRIM);
        exit(EXIT_FAILURE);
    }


    char config[2] = {0};
    config[0] = 0xF2;
    config[1] = 0xFF;
    I2C_Write(0x76, 0xF2, config, 2);

    // Select control measurement register(0xF4)
    // Normal mode, temp and pressure over sampling rate = 1(0x27)
    config[0] = 0xF4;
    config[1] = 0x27;
    I2C_Write(BME280_I2C_ADDR_PRIM, 0xF4, config, 2);
    // Select config register(0xF5)
    // Stand_by time = 1000 ms(0xA0)
    /*config[0] = 0xF5;
    config[1] = 0xA0;
    I2C_Write(0x76, 0xF5, config, 2);
     */

    rslt = bme280_init(&dev);
    printf("Init Res:%hhd\n", rslt);
    for (;;)
    {
        stream_sensor_data_normal_mode(&dev, &bme_out);
        printf("Temperature: %s\t humidity: %s\t pressure: %s\n",
               bme_out.temp, bme_out.humidity, bme_out.pressure);

    }

    //stream_sensor_data_forced_mode(&dev);
}

static void json_handle(struct mg_connection *nc, struct http_message *hm)
{
    char bme_json_out[1024] = {0};
    double result;
    get_BME280_json_data(bme_json_out);
    /* Send headers */
    mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

    /* Compute the result and send it back as a JSON object */
   
    //mg_printf_http_chunk(nc, "%s", bme_json_out );
    mg_send_http_chunk(nc, bme_json_out, strlen(bme_json_out)); /* Send empty chunk, the end of response */

    mg_send_http_chunk(nc, "", 0); /* Send empty chunk, the end of response */
}

static mg_event_handler_t ev_handler(struct mg_connection * mgc, int ev, void * ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev)
    {
    case MG_EV_HTTP_REQUEST:
        if (mg_vcmp(&hm->uri, "/getall") == 0)
        {
            json_handle(mgc, hm);
        }
            //mg_serve_http(mgc, (struct http_message *) ev_data, s_http_server_opts);
            //printf("name:%s\t value:%s",hm->header_names[0],hm->header_values[0] );
            // We have received an HTTP request. Parsed request is contained in `hm`.
            // Send HTTP reply to the client which shows full original request.
        else
        {
            mg_send_head(mgc, 200, hm->message.len, "Content-Type: text/plain");
            mg_printf(mgc, "%.*s", hm->message.len, hm->message.p);
        }
        break;
    default:
        break;
    }
}

void Test_WebServer()
{
    struct mg_mgr mgr;
    struct mg_connection *mgc;
    mg_mgr_init(&mgr, NULL);
    mgc = mg_bind(&mgr, "9090", ev_handler);
    if (mgc == NULL)
    {
        printf("Failed to create socket. \n");
        exit(-1);
    }
    mg_set_protocol_http_websocket(mgc);
    //s_http_server_opts.document_root = "./web_root";
    //s_http_server_opts.enable_directory_listing = "no";
    s_http_server_opts.auth_domain = "localhost";
    while (1)
    {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
}

void Test_SQLite()
{
    sqlite3 * db;
    s8 db_resp = 0;
    //db_resp = sqlite3_open("test.db", &db);
    db_resp = db_init(&db, "test.db");
    if (db_resp == SUCCESS)
    {
        printf("DB Init is Ok\n");
        struct bme_data d1;

        db_create(db, NULL);

        Get_BME280_Data(&d1);
        printf("dt:%s\ttmp:%s\tpres:%s\thum:%s", d1.date_time, d1.temp, d1.pressure, d1.humidity);
        db_resp = db_write(db, NULL, &d1);
        if (SUCCESS == db_resp)
        {
            printf("Create Table is O.K\n");
        }
        db_resp = db_read(db, NULL);

    }
    else
    {
        printf("Opps: %s", sqlite3_errmsg(db));
    }
    char date_time[16] = {0};
    s8 resp = get_date_time(date_time);
    puts(date_time);


}

void Get_BME280_Data(struct bme_data * bme_out)
{
    struct bme280_dev dev;
    s8 rslt = BME280_OK;
    u8 buf[2] = {0};
    u8 date_time[16] = {0};

    dev.dev_id = BME280_I2C_ADDR_PRIM;
    dev.intf = BME280_I2C_INTF;
    dev.read = I2C_Read;
    dev.write = I2C_Write;
    dev.delay_ms = delay_ms;


    fprintf(stdout, "Start Testing BME280 via I2C Protocol...\n");

#if 0 
    if (I2C_SUCCESS == I2C_Init(1, 0x76))
    {
        printf("Protocol Configuration is Ok...\n");
        rslt = I2C_Read(0x76, 0xD0, buf, 1);
        printf("Data Read is %x\n", buf[0]);

    }
#endif
    if (I2C_SUCCESS != I2C_Init(I2C_BUS_1, BME280_I2C_ADDR_PRIM))
    {
        fprintf(stderr, "I2C Initialization Error On Device %x\n",
                BME280_I2C_ADDR_PRIM);
        exit(EXIT_FAILURE);
    }

    char config[2] = {0};
    config[0] = 0xF2;
    config[1] = 0xFF;
    I2C_Write(0x76, 0xF2, config, 2);

    // Select control measurement register(0xF4)
    // Normal mode, temp and pressure over sampling rate = 1(0x27)
    config[0] = 0xF4;
    config[1] = 0x27;
    I2C_Write(BME280_I2C_ADDR_PRIM, 0xF4, config, 2);

    rslt = bme280_init(&dev);

    stream_sensor_data_normal_mode(&dev, bme_out);
    if (SUCCESS == get_date_time(date_time))
    {
        strncpy(bme_out->date_time, date_time, sizeof (date_time));
    }




}

void get_BME280_json_data(char * bme_json_out)
{
    //char json_out[1024] = {0};
    bme_data1 bme_out;
    Get_BME280_Data(&bme_out);
        sprintf(bme_json_out, "{\n"
            "\"date_time\"   :\"%s\" ,\n"
            "\"temperature\" :\"%s\" ,\n"
            "\"humidity\"    :\"%s\" ,\n"
            "\"pressure\"    :\"%s\" \n"
            "}",
            bme_out.date_time,
            bme_out.temp,
            bme_out.humidity,
            bme_out.pressure);
    puts(bme_json_out);
}