/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "bmp280_impl.h"


void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
        printf("%0.2f, %0.2f, %0.2f\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#else
        printf("%ld, %ld, %ld\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#endif
}
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev,
                                      struct bme_data * bme_out)
{
    int8_t rslt;
    uint8_t settings_sel;
    struct bme280_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
    dev->settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    rslt = bme280_set_sensor_settings(settings_sel, dev);

    printf("Temperature, Pressure, Humidity\r\n");
    /* Continuously stream sensor data */
    while (1) {
        rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
        /* Wait for the measurement to complete and print data @25Hz */
        dev->delay_ms(1000);
        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        print_sensor_data(&comp_data);
    }
    return rslt;
}


int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev,
                                      struct bme_data * bme_out)
{
	int8_t rslt = 0;
	uint8_t settings_sel = 0;
	struct bme280_data comp_data;
        char tmpStr[20] = {0};
	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	//while (1) {
		/* Delay while the sensor completes a measurement */
		//dev->delay_ms(1000);
		rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
               
                sprintf(tmpStr, "%ld", comp_data.temperature);
                strncpy(bme_out->temp, tmpStr, sizeof(tmpStr));
                memset(tmpStr, 0, sizeof(tmpStr));
                
                sprintf(tmpStr, "%ld", comp_data.pressure);
                strncpy(bme_out->pressure, tmpStr, sizeof(tmpStr));
                memset(tmpStr, 0, sizeof(tmpStr));
                
                sprintf(tmpStr, "%ld", comp_data.humidity);
                strncpy(bme_out->humidity, tmpStr, sizeof(tmpStr));
                memset(tmpStr, 0, sizeof(tmpStr));


                

		//print_sensor_data(&comp_data);
	//}

	return rslt;
}
