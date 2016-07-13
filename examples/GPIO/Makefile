# usage: 
# 1) have avr compiler and avrdude in $PATH.
# 2) make all
# 3) to program with the wiring pass COM=COMn parameter to make. 
# Ensure that avrdude.conf is in the same calatog as avrdude executable

# -- User definitions ----------------------------

HAL_PATH = ../../HAL
APP_NAME = GPIO

DEFINES = \
  -DDEBUG \
  -DF_CPU=16000000L \
  -DMCU_ATMEGA2560_TQFP100 \
  -DBOARD_ARDUINOMEGA2560

MCU = ATMEGA2560

INCLUDES = \
  -I$(HAL_PATH) \
  -I .
  
SRCS = \
  GPIOtest.cpp

# -- Tools definitions ----------------------------

AS       = avr-as
LD       = avr-ld
CC       = avr-gcc
CPP      = avr-g++
AR       = avr-ar
NM       = avr-nm
STRIP    = avr-strip
OBJCOPY  = avr-objcopy
OBJDUMP  = avr-objdump
SIZE     = avr-size

CFLAGS =  -O2 -std=gnu++1y -pipe -c -W -Wall -Wextra -Winline -pedantic -ffunction-sections 
  
# -- Compile --------------------------------------------------------

CONFIG_NAME = $(APP_NAME)
LIST_PATH = $(CONFIG_NAME)/List
EXE_PATH = $(CONFIG_NAME)/Exe
OBJ_PATH = $(CONFIG_NAME)/Obj

OBJS = $(addprefix $(OBJ_PATH)/, $(notdir %/$(subst .cpp,.o,$(SRCS))))

CFLAGS += $(DEFINES)
CFLAGS += $(INCLUDES)
CFLAGS += -g

LD = $(CPP)
LINKER_FLAGS = -Wl,-Map=$(LIST_PATH)/$(APP_NAME).map -Wl,--gc-sections
LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))

ifeq ($(MCU),ATMEGA2560)
	CFLAGS += -mmcu=atmega2560
	AVRDUDE_TARGET = atmega2560
endif

.PHONY: all directories clean size images

all: directories images size

images: $(EXE_PATH)/$(APP_NAME).elf $(EXE_PATH)/$(APP_NAME).hex

$(OBJ_PATH)/%.o: $(SRCS)
	$(CPP) $(CFLAGS) $(filter %.cpp, $(SRCS)) -o $@

$(OBJS): directories

$(EXE_PATH)/$(APP_NAME).elf: $(OBJS)
	$(LD) $(LINKER_FLAGS) $(OBJS) -o $@

$(EXE_PATH)/$(APP_NAME).hex: $(EXE_PATH)/$(APP_NAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

clean:
	rm -rf $(CONFIG_NAME)

directories:
	@"mkdir" -p $(LIST_PATH)
	@"mkdir" -p $(EXE_PATH)
	@"mkdir" -p $(OBJ_PATH)

ifeq ($(MAKECMDGOALS), fresh)
directories: clean
endif

size: $(EXE_PATH)/$(APP_NAME).elf
	@$(SIZE) -td $(EXE_PATH)/$(APP_NAME).elf

fresh: all

# -- Program --------------------------------------------------------

wiring: $(EXE_PATH)/$(APP_NAME).hex
	avrdude -c wiring -F -v -p$(AVRDUDE_TARGET) -cwiring -P$(COM) -b115200 -D -Uflash:w:$(EXE_PATH)/$(APP_NAME).hex:i
