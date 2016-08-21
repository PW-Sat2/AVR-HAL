# -- Tools definitions --------------------------

AS       = avr-as
LD       = avr-g++
CC       = avr-gcc
CPP      = avr-g++
AR       = avr-ar
NM       = avr-nm
STRIP    = avr-strip
OBJCOPY  = avr-objcopy
OBJDUMP  = avr-objdump
SIZE     = avr-size

CFLAGS = -O2 -std=gnu++1y -c -Wall -Wextra -pedantic -Winline -ffunction-sections -g
CFLAGS += $(CPPFLAGS)

SRCS += $(HAL_PATH)/periph/Analog.cpp

# -- BOARDS -------------------------------------

ifeq ($(BOARD),ARDUINOMEGA2560)
	MCU = ATMEGA2560_TQFP100
	F_CPU = 16000000L
	CFLAGS += -DBOARD_ARDUINOMEGA2560
	BOARD_FOLDER = $(HAL_PATH)/boards/ArduinoMega2560
endif

ifeq ($(BOARD),ARDUINONANO328P_16MHZ)
	MCU = ATMEGA328P_TQFP32
	F_CPU = 16000000L
	CFLAGS += -DBOARD_ARDUINONANO328P_16MHZ
	BOARD_FOLDER = $(HAL_PATH)/boards/ArduinoNano328P
endif

ifeq ($(BOARD),ARDUINONANO328P_8MHZ)
	MCU = ATMEGA328P_TQFP32
	F_CPU = 8000000L
	CFLAGS += -DBOARD_ARDUINONANO328P_8MHZ
	BOARD_FOLDER = $(HAL_PATH)/boards/ArduinoNano328P
endif

ifeq ($(BOARD),EASYAVR128)
	MCU = ATMEGA128A_TQFP64
	F_CPU = 7372800L
	CFLAGS += -DBOARD_ATMEGA128A_TQFP64
	BOARD_FOLDER = $(HAL_PATH)/boards/easyAVR128
endif

# -- MCU ----------------------------------------

ifeq ($(MCU),ATMEGA2560_TQFP100)
	CFLAGS += -DMCU_ATMEGA2560_TQFP100
	CFLAGS += -mmcu=atmega2560
	AVRDUDE_TARGET = atmega2560
endif

ifeq ($(MCU),ATMEGA328P_TQFP32)
	CFLAGS += -DMCU_ATMEGA328P_TQFP32
	CFLAGS += -mmcu=atmega328p
	AVRDUDE_TARGET = m328p
endif

ifeq ($(MCU),ATMEGA128A_TQFP64)
	CFLAGS += -DMCU_ATMEGA128A_TQFP64
	CFLAGS += -mmcu=atmega128
	AVRDUDE_TARGET = m128
endif

# -- Compile ------------------------------------

LIST_PATH = $(APP_NAME)/List
EXE_PATH = $(APP_NAME)/Exe
OBJ_PATH = $(APP_NAME)/Obj

HEX_FILE = $(EXE_PATH)/$(APP_NAME).hex
ELF_FILE = $(EXE_PATH)/$(APP_NAME).elf

OBJS = $(addprefix $(OBJ_PATH)/, $(subst /,^,$(subst .cpp,.o,$(SRCS))))

INCLUDES += \
  -I$(HAL_PATH) \
  -I$(HAL_PATH)/mcu \
  -I$(HAL_PATH)/periph \
  -I$(HAL_PATH)/boards \
  -I$(HAL_PATH)/devices \
  -I$(HAL_PATH)/libs

CFLAGS += $(DEFINES)
CFLAGS += $(INCLUDES)
CFLAGS += -DF_CPU=$(F_CPU)

LINKER_FLAGS = -Wl,-Map=$(LIST_PATH)/$(APP_NAME).map -Wl,--gc-sections 
LINKER_FLAGS += -Wl,-u,vfprintf -lprintf_flt -lm
LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))


.PHONY: params all directories clean size images

all: params directories images size

all_targets: clean
	$(MAKE) all BOARD=ARDUINOMEGA2560
	$(MAKE) all BOARD=ARDUINONANO328P_8MHZ
	$(MAKE) all BOARD=EASYAVR128
	$(MAKE) clean

params: directories
ifdef COM 
	@"cat" $(APP_NAME)/conf | grep -v "COM" | cat > $(APP_NAME)/conf
	@"echo" "COM=$(COM)" >> $(APP_NAME)/conf
endif

ifdef PROGRAMMER
	@"cat" $(APP_NAME)/conf | grep -v "PROGRAMMER" | cat > $(APP_NAME)/conf
	@"echo" PROGRAMMER=$(PROGRAMMER) >> $(APP_NAME)/conf
endif

ifdef BAUD
	@"cat" $(APP_NAME)/conf | grep -v "BAUD" | cat > $(APP_NAME)/conf
	@"echo" BAUD=$(BAUD) >> $(APP_NAME)/conf
endif

images: params $(HEX_FILE) $(ELF_FILE)

$(OBJS): $(SRCS)
	@echo -e "\nCompiling " $(filter $(subst $(OBJ_PATH)/,,$(subst ^,/,$(subst .o,.cpp,$@))), $(SRCS)) "..."
	$(CPP) $(CFLAGS) $(filter $(subst $(OBJ_PATH)/,,$(subst ^,/,$(subst .o,.cpp,$@))), $(SRCS)) -o $@

$(OBJS): directories

$(ELF_FILE): $(OBJS)
	@echo -e "\nLinking..."
	$(LD) $(LINKER_FLAGS) $(OBJS) -o $@

$(HEX_FILE): $(ELF_FILE)
	@echo -e "\nCreating HEX..."
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

clean:
	rm -rf $(APP_NAME)

directories:
	@"mkdir" -p $(APP_NAME)
	@"mkdir" -p $(LIST_PATH)
	@"mkdir" -p $(EXE_PATH)
	@"mkdir" -p $(OBJ_PATH)
	@"touch" $(APP_NAME)/conf

ifeq ($(MAKECMDGOALS), fresh)
directories: clean
endif

size: $(ELF_FILE)
	@echo -e "\nSize:"
	@$(SIZE) -td $(ELF_FILE)

fresh: all

# -- Program ------------------------------------

-include $(APP_NAME)/conf

AVRDUDE_PARAMS = -c$(PROGRAMMER)
ifdef COM
AVRDUDE_PARAMS += -P$(COM)
endif
ifdef BAUD
AVRDUDE_PARAMS += -b$(BAUD)
endif

flash: all
ifndef PROGRAMMER
	$(error No programmer defined)
endif
#ifndef COM
#	ifneq ($(filter wiring arduino,$(PROGRAMMER)),"")
#endif
	avrdude -v -p$(AVRDUDE_TARGET) $(AVRDUDE_PARAMS) -Uflash:w:$(HEX_FILE):i


ifdef BOARD_FOLDER
include $(BOARD_FOLDER)/programmers.make
endif


# -- Utils --------------------------------------

gitignores: .gitignore

.gitignore: Makefile
	echo $(APP_NAME) > .gitignore
	