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
#include "periph/gpio.h"
#include "periph/pwm.h"
#include "periph/adc.h"
#include "xtimer.h"
#include "kernel_defines.h"

#define PERIOD_LOOPLED 40000
#define PERIOD_LOOPRNG 250000

static const uint8_t lut[] = { 0, 1, 2, 3, 4, 6, 8, 12, 16, 23, 32, 45, 64, 90, 128, 255 };

typedef struct {
    const pwm_t pwm;
    const uint8_t ch;
    int8_t state;
    uint8_t value;
} led_t;

static led_t leds[] = {
    {.pwm = PWM_DEV(0), .ch = 0, .state = 0, .value = 0},
    {.pwm = PWM_DEV(0), .ch = 1, .state = 0, .value = 0},
    {.pwm = PWM_DEV(0), .ch = 2, .state = 0, .value = 0},
    {.pwm = PWM_DEV(0), .ch = 3, .state = 0, .value = 0},
    {.pwm = PWM_DEV(1), .ch = 0, .state = 0, .value = 0},
    {.pwm = PWM_DEV(1), .ch = 1, .state = 0, .value = 0},
    {.pwm = PWM_DEV(1), .ch = 2, .state = 0, .value = 0},
    {.pwm = PWM_DEV(1), .ch = 3, .state = 0, .value = 0},
};

static const char card[] = \
    "                                            .-\"\"-.\n" \
    "                                           (___/\\ \\\n" \
    "                         ,                (|^ ^ ) )\n" \
    "                        /(               _)_\\=_/  (\n" \
    "                  ,..__/ `\\          ____(_/_ ` \\   )\n" \
    "                   `\\    _/        _/---._/(_)_  `\\ (\n" \
    "                     '--\\ `-.__..-'    /.    (_), |  )\n" \
    "                         `._        ___\\_____.'_| |__/\n" \
    "                            `~----\"`   `-.........'\n" \
    "\n" \
    "                         Hey Leo du alte Meerjungfrau!\n" \
    "\n" \
    "                           Wir haben gehört, dass du\n" \
    "\n" \
    "                    A) Ein kleiner Hacker bist\n" \
    "                    B) Super gerne im Wasser planscht\n" \
    "                    C) Eh ein total töfter Typ bist <3\n" \
    "                    E) Listen magst\n" \
    "                    G) Regel- und Gesetzmäßigkeiten schätzt\n" \
    "\n" \
    "                   Wir würden dich gerne an einem Tag deiner\n" \
    "               Wahl auf einen Ausflug in das $ERLEBNISBAD mit\n" \
    "                allem drum und dran entführen, dort einen hammer\n" \
    "             geilen Tag mit dir verbringen, abends noch schön was\n" \
    "                zusammen essen und im Anschluss ordentlich einen\n" \
    "                     (zwei, drei, drölf...) mit dir heben!\n" \
    "\n" \
    "                   Wir freuen uns auf einen unvergesslichen,\n" \
    "                       feucht-fröhlichen Badetag mit dir!\n" \
    "\n" \
    "                                In diesem Sinne\n" \
    "\n" \
    "                      ~                  ~\n" \
    "               *                   *                *       *\n" \
    "                            *               *\n" \
    "            ~       *                *         ~    *\n" \
    "                        *       ~        *              *   ~\n" \
    "                            )         (         )              *\n" \
    "              *    ~     ) (_)   (   (_)   )   (_) (  *\n" \
    "                     *  (_) # ) (_) ) # ( (_) ( # (_)       *\n" \
    "                        _#.-#(_)-#-(_)#(_)-#-(_)#-.#_\n" \
    "            *         .' #  # #  #  # # #  #  # #  # `.   ~     *\n" \
    "                     :   #    #  #  #   #  #  #    #   :\n" \
    "              ~      :.       #     #   #     #       .:      *\n" \
    "                  *  | `-.__                     __.-' | *\n" \
    "                     |      `````\"\"\"\"\"\"\"\"\"\"\"`````      |         *\n" \
    "               *     |         | ||\\ |~)|~)\\ /         |\n" \
    "                     |         |~||~\\|~ |~  |          |       ~\n" \
    "             ~   *   |                                 | *\n" \
    "                     |      |~)||~)~|~| ||~\\|\\ \\ /     |         *\n" \
    "             *    _.-|      |~)||~\\ | |~|| /|~\\ |      |-._\n" \
    "                .'   '.      ~            ~           .'   `.  *\n" \
    "                :      `-.__                     __.-'      :\n" \
    "                 `.         `````\"\"\"\"\"\"\"\"\"\"\"`````         .'\n" \
    "                   `-.._                             _..-'\n" \
    "                        `````\"\"\"\"-----------\"\"\"\"`````\n" \
    "\n" \
    "\n" \
    "         Aylinn, Babolin, Ferdinand, Fred, Günthi, Hannes, Jan-Niklas,\n" \
    "                         Jürgen, Luis, Lukas und Tobby\n" \
    "\n" \
    "                                        _,.---.---.---.--.._\n" \
    "                              _.-' `--.`---.`---'-. _,`--.._\n" \
    "                             /`--._ .'.     `.     `,`-.`-._\\\n" \
    "                            ||   \\  `.`---.__`__..-`. ,'`-._/\n" \
    "                       _  ,`\\ `-._\\   \\    `.    `_.-`-._,``-.\n" \
    "                    ,`   `-_ \\/ `-.`--.\\    _\\_.-'\\__.-`-.`-._`.\n" \
    "                   (_.o> ,--. `._/'--.-`,--`  \\_.-'       \\`-._ \\\n" \
    "                    `---'    `._ `---._/__,----`           `-. `-\\\n" \
    "                              /_, ,  _..-'                    `-._\\\n" \
    "                              \\_, \\/ ._(\n" \
    "                               \\_, \\/ ._\\\n" \
    "                                `._,\\/ ._\\\n" \
    "                                  `._// ./`-._\n" \
    "                                    `-._-_-_.-'\n" \
    "\n";

void happy_bithday(void)
{
    gpio_init(GPIO_PIN(PORT_B, 2), GPIO_IN);
    char enc = gpio_read(GPIO_PIN(PORT_B, 2)) ? 0x00 : 0x25;
    for (unsigned i = 0; i < ARRAY_SIZE(card); i++) {
        putchar(card[i] ^ enc);
    }
}

int main(void)
{
    uint64_t loopLed = xtimer_now_usec64();
    uint64_t loopRng = xtimer_now_usec64();

    pwm_init(PWM_DEV(0), PWM_LEFT, 1000, 0xff);
    pwm_init(PWM_DEV(1), PWM_LEFT, 1000, 0xff);
    adc_init(ADC_LINE(0));

    happy_bithday();

    while (1) {
        uint64_t now = xtimer_now_usec64();

        if (loopLed < now) {
            loopLed += PERIOD_LOOPLED;

            for (unsigned i = 0; i < ARRAY_SIZE(leds); i++) {
                leds[i].value += leds[i].state;
                pwm_set(leds[i].pwm, leds[i].ch, lut[leds[i].value]);
                if (leds[i].value == ARRAY_SIZE(lut) - 1) leds[i].state = -1;
                else if (leds[i].value == 0) leds[i].state = 0;
            }
        }

        if (loopRng < now) {
            loopRng += PERIOD_LOOPRNG;

            uint8_t rng = 0;
            for (int i = 0; i < 4; i++) {
                rng = rng << 1;
                rng = rng | (adc_sample(ADC_LINE(0), ADC_RES_12BIT) & 1);
            }

            if (rng > ARRAY_SIZE(leds)) continue;
            if (leds[rng].state != 0) continue;
            leds[rng].state = 1;
        }
    }

    return 0;
}
