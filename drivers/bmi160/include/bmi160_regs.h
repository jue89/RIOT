/*
 * Copyright (C) 2019 Juergen Fitschen
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef BMI160_REGS_H
#define BMI160_REGS_H

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @name    Register addresses
 * @{
 */
#define BMI160_REG_CHIP_ID          (0x00) /**< Device ID */
#define BMI160_REG_CMD              (0x7E) /**< Command register **/
#define BMI160_REG_DATA_GYR_X       (0x0C) /**< X-axis gyroscope **/
#define BMI160_REG_DATA_GYR_Y       (0x0E) /**< Y-axis gyroscope **/
#define BMI160_REG_DATA_GYR_Z       (0x10) /**< Z-axis gyroscope **/
#define BMI160_REG_DATA_ACC_X       (0x12) /**< X-axis accelerometer **/
#define BMI160_REG_DATA_ACC_Y       (0x14) /**< Y-axis accelerometer **/
#define BMI160_REG_DATA_ACC_Z       (0x16) /**< Z-axis accelerometer **/
/** @} */

/**
 * @name    Device ID for BMI160
 * @{
 */
#define BMI160_CHIP_ID              (0xD1)
/** @} */

/**
 * @name    BMI160 commands
 * @{
 */
#define BMI160_CMD_SOFTRESET        (0xB6)
#define BMI160_CMD_ACC_PM_NORMAL    (0x11)
#define BMI160_CMD_GYR_PM_NORMAL    (0x15)
/** @} */

/**
 * @name    BMI160 command delays
 * @{
 */
#define BMI160_ACC_PMU_USLEEP       (3800)
#define BMI160_GYR_PMU_USLEEP       (80000)
#define BMI160_SOFTRESET_USLEEP     (1000)
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* BMI160_REGS_H */
