include $(HAL_PATH)/boards/boards.make
include $(HAL_PATH)/mcu/mcu.make

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

CFLAGS += -O2 -std=gnu++1y -c -Wall -Wextra -Winline -ffunction-sections -g $(USER_CFLAGS)
CFLAGS += $(CPPFLAGS)

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
ifdef F_CPU
CFLAGS += -DF_CPU=$(F_CPU)
else
#$(error "No F_CPU defined! Provide in board BSP (board.make), by Makefile or by command line (F_CPU=...)")
endif

LINKER_FLAGS = -Wl,-Map=$(LIST_PATH)/$(APP_NAME).map -Wl,--gc-sections 
LINKER_FLAGS += -Wl,-u,vfprintf -lprintf_flt -lm
LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))


.PHONY: params all directories clean size images force

all: params directories images size

all_targets: clean
	$(MAKE) all BOARD=ARDUINOMEGA2560
	$(MAKE) clean
	$(MAKE) all BOARD=ARDUINONANO328P F_CPU=16000000
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

ifndef BOARD
	@"echo" "No BOARD defined. Provide BOARD=...!!!"
	false;
endif

images: params $(HEX_FILE) $(ELF_FILE)

$(OBJS): force
	@echo "\nCompiling " $(filter $(subst $(OBJ_PATH)/,,$(subst ^,/,$(subst .o,.cpp,$@))), $(SRCS)) "..."
	$(CPP) $(CFLAGS) $(filter $(subst $(OBJ_PATH)/,,$(subst ^,/,$(subst .o,.cpp,$@))), $(SRCS)) -o $@
	
force: ;

$(OBJS): directories

$(ELF_FILE): $(OBJS)
	@echo "\nLinking..."
	$(LD) $(LINKER_FLAGS) $(OBJS) -o $@

$(HEX_FILE): $(ELF_FILE)
	@echo "\nCreating HEX..."
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
	@echo "\nSize:"
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


ifneq ("$(wildcard $(BOARD_FOLDER)/programmers.make)","")
include $(BOARD_FOLDER)/programmers.make
endif


# -- Utils --------------------------------------

gitignores: .gitignore

.gitignore: Makefile
	echo $(APP_NAME) > .gitignore
	
