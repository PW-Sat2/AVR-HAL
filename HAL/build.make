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

CFLAGS = -O2 -std=gnu++1y -c -Wall -Wextra -Winline -ffunction-sections -g
CFLAGS += $(CPPFLAGS)

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
	CFLAGS += -DBOARD_EASYAVR128
	BOARD_FOLDER = $(HAL_PATH)/boards/easyAVR128
endif

ifeq ($(BOARD),EVB_MEGA644P_16MHZ)
	MCU = ATMEGA644P_DIP40
	F_CPU = 16000000L
	CFLAGS += -DBOARD_EVB_MEGA644P_16MHZ
	BOARD_FOLDER = $(HAL_PATH)/boards/easyAVR128
endif

ifeq ($(BOARD),EVB_ATMEGA324P)
	MCU = ATMEGA324P_44
	F_CPU = 8000000L
	CFLAGS += -DBOARD_EVB_ATMEGA324P
	BOARD_FOLDER = $(HAL_PATH)/boards/EVB_ATMega324p
endif

ifeq ($(BOARD),SUNS_EM3)
	MCU = ATMEGA324A_44
	F_CPU = 8000000L
	CFLAGS += -DBOARD_SUNS_EM3
	BOARD_FOLDER = $(HAL_PATH)/boards/SUNS_EM3
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
	CFLAGS += -mmcu=atmega128a
	AVRDUDE_TARGET = m128
endif

ifeq ($(MCU),ATMEGA644P_DIP40)
	CFLAGS += -DMCU_ATMEGA644P_DIP40
	CFLAGS += -mmcu=atmega644p
	AVRDUDE_TARGET = m644p
endif

ifeq ($(MCU),ATMEGA164P_44)
	CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
	CFLAGS += -mmcu=atmega164p
	AVRDUDE_TARGET = m164p
endif

ifeq ($(MCU),ATMEGA324P_44)
	CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
	CFLAGS += -mmcu=atmega324p
	AVRDUDE_TARGET = m324p
endif

ifeq ($(MCU),ATMEGA644P_44)
	CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
	CFLAGS += -mmcu=atmega664p
	AVRDUDE_TARGET = m664p
endif


ifeq ($(MCU),ATMEGA164A_44)
	CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
	CFLAGS += -mmcu=atmega164a
	AVRDUDE_TARGET = m164pa
endif

ifeq ($(MCU),ATMEGA324A_44)
	CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
	CFLAGS += -mmcu=atmega324a
	AVRDUDE_TARGET = m324pa
endif

ifeq ($(MCU),ATMEGA644A_44)
	CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
	CFLAGS += -mmcu=atmega664a
	AVRDUDE_TARGET = m664pa
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
  -I$(HAL_PATH)/libs \
  -I$(HAL_PATH)/libs/device_supports \
  -I$(HAL_PATH)/libs/std

CFLAGS += $(DEFINES)
CFLAGS += $(INCLUDES)
CFLAGS += -DF_CPU=$(F_CPU)

LINKER_FLAGS = -Wl,-Map=$(LIST_PATH)/$(APP_NAME).map -Wl,--gc-sections 
LINKER_FLAGS += -Wl,-u,vfprintf -lprintf_flt -lm
LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))


.PHONY: params all directories clean size images force

all: params directories images size

all_targets: clean
	$(MAKE) all BOARD=ARDUINOMEGA2560
	$(MAKE) clean
	$(MAKE) all BOARD=ARDUINONANO328P_8MHZ
	$(MAKE) clean
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

$(OBJS): force
	@echo -e "\nCompiling " $(filter $(subst $(OBJ_PATH)/,,$(subst ^,/,$(subst .o,.cpp,$@))), $(SRCS)) "..."
	$(CPP) $(CFLAGS) $(filter $(subst $(OBJ_PATH)/,,$(subst ^,/,$(subst .o,.cpp,$@))), $(SRCS)) -o $@
	
force: ;

$(OBJS): directories

$(ELF_FILE): $(OBJS)
	@echo -e "\nLinking..."
	$(LD) $(LINKER_FLAGS) $(OBJS) -o $@

$(HEX_FILE): $(ELF_FILE)
	@echo -e "\nCreating HEX..."
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

clean:
	rm -rf $(APP_NAME)

directories: $(APP_NAME) $(LIST_PATH) $(EXE_PATH) $(OBJ_PATH) $(APP_NAME)/conf

$(APP_NAME):
	@"mkdir" -p $(APP_NAME)
	
$(LIST_PATH):
	@"mkdir" -p $(LIST_PATH)

$(EXE_PATH):
	@"mkdir" -p $(EXE_PATH)

$(OBJ_PATH):
	@"mkdir" -p $(OBJ_PATH)

$(APP_NAME)/conf: $(APP_NAME)
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
	