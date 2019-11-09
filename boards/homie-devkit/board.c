/*
 * Copyright (C) 2019 Juergen Fitschen <me@jue.yt>
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_homie-devkit
 * @{
 *
 * @file
 * @brief       Board specific implementations for the Homie Devkit board
 *
 * @author      Juergen Fitschen <me@jue.yt>
 *
 * @}
 */

#include "board.h"
#include "periph/gpio.h"

void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    /* initialize the boards LEDs */
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init(LEDTX_PIN, GPIO_OUT);
    gpio_init(LEDRX_PIN, GPIO_OUT);
}
