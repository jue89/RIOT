# name of your application
APPLICATION = hello-world

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

USEMODULE += ztimer_usec
USEMODULE += ztimer_msec
USEMODULE += ztimer_periph_rtt

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

CFLAGS+='-DCONFIG_ZTIMER_PERIPH_TIMER_PM_LAYER=1'

include $(RIOTBASE)/Makefile.include
