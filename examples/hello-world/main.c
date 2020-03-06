/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Hello World application
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include "ztimer.h"

void cb (void * ctx) {
    (void) ctx;
    puts("CB!");
}

int main(void)
{
    ztimer_t timer = {.callback = cb};

    puts("Hello World!");

    printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    printf("This board features a(n) %s MCU.\n", RIOT_MCU);

    while (true) {
        puts("Zzzzz...");
        ztimer_sleep(ZTIMER_MSEC, 3000);
        puts("Good morning");
        ztimer_set(ZTIMER_USEC, &timer, 1000000);
        ztimer_sleep(ZTIMER_USEC, 500000);
    }

    return 0;
}
