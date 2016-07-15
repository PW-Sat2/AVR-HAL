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

CFLAGS = -O2 -std=gnu++1y -c -Wall -Wextra -pedantic -Winline -ffunction-sections
CFLAGS += $(CPPFLAGS)

# -- BOARDS -------------------------------------

ifeq ($(BOARD),ARDUINOMEGA2560)
	MCU = ATMEGA2560_TQFP100
	F_CPU = 16000000L
	CFLAGS += -DBOARD_ARDUINOMEGA2560
	BOARD_FOLDER = $(HAL_PATH)/boards/ArduinoMega2560
endif

ifeq ($(BOARD),ARDUINONANO328P)
	MCU = ATMEGA328P_TQFP32
	F_CPU = 16000000L
	CFLAGS += -DBOARD_ARDUINONANO328P
	BOARD_FOLDER = $(HAL_PATH)/boards/ArduinoNano328P
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

# -- Compile ------------------------------------

LIST_PATH = $(APP_NAME)/List
EXE_PATH = $(APP_NAME)/Exe
OBJ_PATH = $(APP_NAME)/Obj

HEX_FILE = $(EXE_PATH)/$(APP_NAME).hex
ELF_FILE = $(EXE_PATH)/$(APP_NAME).elf


OBJS = $(addprefix $(OBJ_PATH)/, $(notdir %/$(subst .cpp,.o,$(SRCS))))

INCLUDES += \
  -I$(HAL_PATH)

CFLAGS += $(DEFINES)
CFLAGS += $(INCLUDES)
CFLAGS += -DF_CPU=$(F_CPU)

LINKER_FLAGS = -Wl,-Map=$(LIST_PATH)/$(APP_NAME).map -Wl,--gc-sections
LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))


.PHONY: params all directories clean size images

all: params directories images size


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

$(OBJ_PATH)/%.o: $(SRCS)
	$(CPP) $(CFLAGS) $(filter %.cpp, $(SRCS)) -o $@

$(OBJS): directories

$(ELF_FILE): $(OBJS)
	$(LD) $(LINKER_FLAGS) $(OBJS) -o $@

$(HEX_FILE): $(ELF_FILE)
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
ifndef COM
ifneq ($(filter wiring arduino,$(PROGRAMMER)),"")
	$(error No COM port for programmer specified)
endif
endif
	avrdude -F -v -p$(AVRDUDE_TARGET) $(AVRDUDE_PARAMS) -D -Uflash:w:$(HEX_FILE):i

include $(BOARD_FOLDER)/programmers.make