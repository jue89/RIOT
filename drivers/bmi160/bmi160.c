/*
 * Copyright (C) 2019 Juergen Fitschen
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "assert.h"
#include "periph/i2c.h"
#include "byteorder.h"
#include "xtimer.h"
#include "bmi160.h"
#include "bmi160_regs.h"
#include "bmi160_params.h"

#define ENABLE_DEBUG        (0)
#include "debug.h"

#define BMI160_BUS                 (dev->params.i2c)
#define BMI160_ADDR                (dev->params.addr)

int bmi160_init(bmi160_t *dev, const bmi160_params_t* params)
{
    uint8_t reg;
    int rc;

    assert(dev && params);

    /* Get device descriptor */
    dev->params = *params;

    /* Acquire exclusive access */
    i2c_acquire(BMI160_BUS);

    /* Test if the target device responds */
    rc = i2c_read_reg(BMI160_BUS, BMI160_ADDR, BMI160_REG_CHIP_ID, &reg, 0);
    if (rc != 0) {
        i2c_release(BMI160_BUS);
        DEBUG("[bmi160] init - error: i2c failed\n");
        return BMI160_NOI2C;
    }
    if (reg != BMI160_CHIP_ID) {
        i2c_release(BMI160_BUS);
        DEBUG("[bmi160] init - error: invalid id value [0x%02x]\n", (int)reg);
        return BMI160_NODEV;
    }

    /* Issue software reset */
    i2c_write_reg(BMI160_BUS, BMI160_ADDR, BMI160_REG_CMD, BMI160_CMD_SOFTRESET, 0);
    xtimer_usleep(BMI160_SOFTRESET_USLEEP);

    /* Enable accelerometer and gyroscope */
    i2c_write_reg(BMI160_BUS, BMI160_ADDR, BMI160_REG_CMD, BMI160_CMD_ACC_PM_NORMAL, 0);
    xtimer_usleep(BMI160_ACC_PMU_USLEEP);
    i2c_write_reg(BMI160_BUS, BMI160_ADDR, BMI160_REG_CMD, BMI160_CMD_GYR_PM_NORMAL, 0);
    xtimer_usleep(BMI160_GYR_PMU_USLEEP);

    /* Release the bus */
    i2c_release(BMI160_BUS);

    DEBUG("[bmi160] init: successful\n");

    return BMI160_OK;
}

void bmi160_read(const bmi160_t *dev, bmi160_data_t *gyr, bmi160_data_t *acc)
{
    int16_t buffer[6];
    size_t offset;
    size_t len;

    assert(dev && (acc || gyr));

    /* Check which sensor shall be read */
    if (gyr && !acc) {
        len = 6;
        offset = 0;
    }
    else if (!gyr && acc) {
        len = 6;
        offset = BMI160_REG_DATA_ACC_X - BMI160_REG_DATA_GYR_X;
    }
    else {
        len = 12;
        offset = 0;
    }

    /* Read data registers from BMI160 */
    i2c_acquire(BMI160_BUS);
    i2c_read_regs(BMI160_BUS, BMI160_ADDR, BMI160_REG_DATA_GYR_X + offset, ((void *) buffer) + offset, len, 0);
    i2c_release(BMI160_BUS);

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    /* BMI160 returns value in little endian, so swap is needed on big endian platforms. */
    for (int i = 0; i < 6; i++) {
        buffer[i] = byteorder_swaps((uint16_t)buffer[i]);
    }
#endif

    /* Set results */
    if (gyr) {
        gyr->x = buffer[0];
        gyr->y = buffer[1];
        gyr->z = buffer[2];
    }
    if (acc) {
        acc->x = buffer[3];
        acc->y = buffer[4];
        acc->z = buffer[5];
    }
}
