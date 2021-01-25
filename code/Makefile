# Default Makefile, for host native GNRC-based networking

# name of your application
APPLICATION = gcoap_example

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/RIOT

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Specify the mandatory networking modules
USEMODULE += gnrc_ipv6_default
USEMODULE += gcoap
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo

# Required by gcoap example
USEMODULE += od
USEMODULE += fmt
# Add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += saul_default

USEMODULE += bme280_i2c
USEMODULE += sx1272  # for a SX1272 radio device
USEMODULE += semtech_loramac_rx
USEMODULE += tinycbor_float
USEMODULE += xtimer

USEMODULE += periph_uart

USEPKG += semtech-loramac
USEPKG += tinycbor
USEPKG += minmea

USEMODULE += apa102
USEMODULE += color

# Higher number = lower SF and higher bitrate/s. 
# [DEFAULT]DR_0= is SF12 with 250b/s (SF11 is 440b/s then doubling each step)
CFLAGS += -DLORAMAC_DEFAULT_DR=LORAMAC_DR_4
# CFLAGS += -DSX127X_PARAM_PASELECT=SX127X_PA_BOOST

CFLAGS += -DBMX280_PARAM_I2C_ADDR=0x76

LORA_REGION = EU868

USEMODULE += esp_wifi

WIFI_SSID ?= "ssid"
WIFI_PASS ?= "password"

#CFLAGS += -DBMX280_PARAM_I2C_ADDR=0x76


CFLAGS += -DESP_WIFI_SSID=\"$(WIFI_SSID)\"
CFLAGS += -DESP_WIFI_PASS=\"$(WIFI_PASS)\"

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# For now this goes after the inclusion of Makefile.include so Kconfig symbols
# are available. Only set configuration via CFLAGS if Kconfig is not being used
# for this module.
ifndef CONFIG_KCONFIG_MODULE_GCOAP
## Uncomment to redefine port, for example use 61616 for RFC 6282 UDP compression.
#GCOAP_PORT = 5683
#CFLAGS += -DCONFIG_GCOAP_PORT=$(GCOAP_PORT)

## Uncomment to redefine request token length, max 8.
#GCOAP_TOKENLEN = 2
#CFLAGS += -DCONFIG_GCOAP_TOKENLEN=$(GCOAP_TOKENLEN)

# Increase from default for confirmable block2 follow-on requests
GCOAP_RESEND_BUFS_MAX ?= 2
CFLAGS += -DCONFIG_GCOAP_RESEND_BUFS_MAX=$(GCOAP_RESEND_BUFS_MAX)
endif

# LED strip count and brightness
CFLAGS += -DN_LEDS=2
CFLAGS += -DLED_BRIGHTNESS=128