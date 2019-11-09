/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_stm32f0discovery
 * @{
 *
 * @file
 * @brief       Board specific definitions for the STM32F0Discovery evaluation board.
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Sebastian Meiling <s@mlng.net>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name DOSE configuration
 * @{
 */
#define DOSE_PARAM_UART        UART_DEV(2)
#define DOSE_PARAM_SENSE_PIN   GPIO_PIN(PORT_C, 12)
/** @}*/

/**
 * @name Macros for controlling the on-board LEDs.
 * @{
 */
#define LED0_PIN               GPIO_PIN(PORT_B, 9)
#define LEDTX_PIN              GPIO_PIN(PORT_D, 2)
#define LEDRX_PIN              GPIO_PIN(PORT_B, 8)

#define LED0_PORT              GPIOB
#define LEDTX_PORT             GPIOD
#define LEDRX_PORT             GPIOB
#define LED0_MASK              (1 << 9)
#define LEDTX_MASK             (1 << 2)
#define LEDRX_MASK             (1 << 8)

#define LED0_ON                (LED0_PORT->BSRR = LED0_MASK)
#define LED0_OFF               (LED0_PORT->BRR  = LED0_MASK)
#define LED0_TOGGLE            (LED0_PORT->ODR ^= LED0_MASK)
#define LEDTX_ON               (LEDTX_PORT->BSRR = LEDTX_MASK)
#define LEDTX_OFF              (LEDTX_PORT->BRR  = LEDTX_MASK)
#define LEDTX_TOGGLE           (LEDTX_PORT->ODR ^= LEDTX_MASK)
#define LEDRX_ON               (LEDRX_PORT->BSRR = LEDRX_MASK)
#define LEDRX_OFF              (LEDRX_PORT->BRR  = LEDRX_MASK)
#define LEDRX_TOGGLE           (LEDRX_PORT->ODR ^= LEDRX_MASK)
/** @} */

/**
 * @brief Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

/**
 * @name    xtimer configuration
 * @{
 */
#define XTIMER_WIDTH           (16)
#define XTIMER_BACKOFF         (19)
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
