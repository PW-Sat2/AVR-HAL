#-Compiler type definition---------------------
COMPILER_TYPE = GCC
COMPILER_AND_MICRO_TYPE = GCC_AVR
#-Tools definitions----------------------------
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

CFLAGS =  -O2 -std=gnu++1y -pipe -c -W -Wall -Wextra -pedantic -ffunction-sections -mmcu=atmega2560


HAL_PATH = ../../HAL
APP_NAME = GPIO
CONFIG_NAME = $(APP_NAME)
LIST_PATH = $(CONFIG_NAME)/List
EXE_PATH = $(CONFIG_NAME)/Exe
OBJ_PATH = $(CONFIG_NAME)/Obj

DEFINES = \
  -DDEBUG \
  -DF_CPU=16000000L \
  -DMCU_ATMEGA2560_TQFP100 \
  -DBOARD_ARDUINOMEGA2560

INCLUDES = \
  -I$(HAL_PATH) \
  -I .
  
SRCS = \
  GPIOtest.cpp

OBJS = $(addprefix $(OBJ_PATH)/, $(notdir %/$(subst .cpp,.o,$(SRCS))))

CFLAGS += $(DEFINES)
CFLAGS += $(INCLUDES)
CFLAGS += -g

LD = $(CC)
LINKER_FLAGS = -Wl,-Map=$(LIST_PATH)/$(APP_NAME).map -Wl,--gc-sections
LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))

.PHONY: all directories clean size images

all: directories images size

images: $(EXE_PATH)/$(APP_NAME).elf $(EXE_PATH)/$(APP_NAME).hex $(EXE_PATH)/$(APP_NAME).srec $(EXE_PATH)/$(APP_NAME).bin

$(OBJ_PATH)/%.o: $(SRCS)
	$(CC) $(CFLAGS) $(filter %.cpp, $(SRCS)) -o $@

$(OBJS): directories

$(EXE_PATH)/$(APP_NAME).elf: $(OBJS)
	$(LD) $(LINKER_FLAGS) $(OBJS) -o $@

$(EXE_PATH)/$(APP_NAME).srec: $(EXE_PATH)/$(APP_NAME).elf
	$(OBJCOPY) -O srec --srec-len 128 -R .eeprom $^ $@

$(EXE_PATH)/$(APP_NAME).hex: $(EXE_PATH)/$(APP_NAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

$(EXE_PATH)/$(APP_NAME).bin: $(EXE_PATH)/$(APP_NAME).elf
	$(OBJCOPY) -O binary --strip-debug --strip-unneeded -R .eeprom $^ $@

clean:
	rm -rf $(CONFIG_NAME)

directories:
	@"mkdir" -p $(LIST_PATH)
	@"mkdir" -p $(EXE_PATH)
	@"mkdir" -p $(OBJ_PATH)

size: $(EXE_PATH)/$(APP_NAME).elf
	@$(SIZE) -td $(EXE_PATH)/$(APP_NAME).elf

ifeq ($(MAKECMDGOALS), fresh)
directories: clean
endif

fresh: all

program: $(EXE_PATH)/$(APP_NAME).hex
	avrdude -c wiring -F -v -patmega2560 -cwiring -PCOM4 -b115200 -D -Uflash:w:$(EXE_PATH)/$(APP_NAME).hex:i -C"C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf"
