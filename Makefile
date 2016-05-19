ifeq ($(RTE_SDK),)
$(error "Please define RTE_SDK environment variable")
endif

# Default target, can be overridden by command line or environment
RTE_TARGET ?= x86_64-native-linuxapp-gcc

include $(RTE_SDK)/mk/rte.vars.mk

# binary name
APP=tcpreplay

# all source are stored in SRCS-y
SRC_DIR= src
SOURCES= tcpreplay_args.c   tcpreplay_log.c   tcpreplay_main.c tcpreplay_global.c tcpreplay_netport.c

SRCS-y += $(addprefix $(SRC_DIR)/, $(SOURCES))

CFLAGS += -O3  -g
LDLIBS += -lncurses

include $(RTE_SDK)/mk/rte.extapp.mk
