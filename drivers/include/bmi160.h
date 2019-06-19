/*
 * Copyright (C) 2019 Juergen Fitschen
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_bmi160 BMI160 3-Axis accelerometer and gyroscope
 * @ingroup     drivers_sensors
 * @brief       Device driver interface for the BMI160
 *
 * This driver provides @ref drivers_saul capabilities.
 * @{
 *
 * @file
 * @brief       Interface definition for the BMI160
 *
 * @author      Juergen Fitschen <me@jue.yt>
 */

#ifndef BMI160_H
#define BMI160_H

#ifdef __cplusplus
extern "C" {
#endif

#include "periph/i2c.h"

/**
 * @brief   Possible BMI160 hardware addresses (wiring specific)
 */
enum {
    BMI160_ADDR_68 = 0x68,         /**< I2C device address if Alt addr pin is high */
    BMI160_ADDR_69 = 0x69,         /**< I2C device address if Alt addr pin is low */
};

/**
 * @brief   Named return values
 */
enum {
    BMI160_OK          =  0,       /**< everything was fine */
    BMI160_DATA_READY  =  1,       /**< new data ready to be read */
    BMI160_NOI2C       = -1,       /**< I2C communication failed */
    BMI160_NODEV       = -2,       /**< no BMI160 device found on the bus */
    BMI160_NODATA      = -3        /**< no data available */
};

/**
 * @brief   BMI160 result vector struct
 */
typedef struct {
    int16_t x;                     /**< X-Axis measurement result */
    int16_t y;                     /**< Y-Axis measurement result */
    int16_t z;                     /**< Z-Axis measurement result */
} bmi160_data_t;

/**
 * @brief   Configuration struct for the BMI160 sensor
 */
typedef struct {
    i2c_t i2c;                     /**< I2C device which is used */
    uint8_t addr;                  /**< I2C address */
} bmi160_params_t;

/**
 * @brief   Device descriptor for the BMI160 sensor
 */
typedef struct {
    bmi160_params_t params;        /**< Device configuration */
} bmi160_t;

/**
 * @brief   Initialize the BMI160 driver.
 *
 * @param[out] dev          device descriptor of accelerometer to initialize
 * @param[in]  params       configuration parameters
 *
 * @return                  BMI160_OK on success
 * @return                  BMI160_NOI2C if initialization of I2C bus failed
 * @return                  BMI160_NODEV if device test failed
 */
int bmi160_init(bmi160_t *dev, const bmi160_params_t* params);

/**
 * @brief   Read sensor data
 *
 * @param[in]  dev          device descriptor of accelerometer
 * @param[out] acc          accelerometer data (omitted if set to NULL)
 * @param[out] gyr          gyroscope data (omitted if set to NULL)
 */
void bmi160_read(const bmi160_t *dev, bmi160_data_t *gyr, bmi160_data_t *acc);

#ifdef __cplusplus
}
#endif

#endif /* BMI160_H */
/** @} */
