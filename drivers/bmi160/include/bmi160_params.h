/*
 * Copyright (C) 2019 Juergen Fitschen
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_bmi160
 * @{
 *
 * @file
 * @brief       Default configuration for BMI160 devices
 *
 * @author      Juergen Fitschen <me@jue.yt>
 */

#ifndef BMI160_PARAMS_H
#define BMI160_PARAMS_H

#include "board.h"
#include "bmi160.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters for the BMI160 driver
 * @{
 */
#ifndef BMI160_PARAM_I2C
#define BMI160_PARAM_I2C           (I2C_DEV(0))
#endif

#ifndef BMI160_PARAM_ADDR
#define BMI160_PARAM_ADDR          (BMI160_ADDR_69)
#endif

#ifndef BMI160_PARAMS
#define BMI160_PARAMS              { .i2c    = BMI160_PARAM_I2C,           \
                                     .addr   = BMI160_PARAM_ADDR }
#endif
/**@}*/

/**
 * @brief   BMI160 configuration
 */
static const bmi160_params_t bmi160_params[] =
{
    BMI160_PARAMS
};

#ifdef __cplusplus
}
#endif

#endif /* BMI160_PARAMS_H */
