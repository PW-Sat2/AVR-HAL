# -- MCU ----------------------------------------

ifeq ($(MCU),ATMEGA2560_TQFP100)
  CFLAGS += -DMCU_ATMEGA2560_TQFP100
  CFLAGS += -mmcu=atmega2560
  AVRDUDE_TARGET = atmega2560
else ifeq ($(MCU),ATMEGA328P_TQFP32)
  CFLAGS += -DMCU_ATMEGA328P_TQFP32
  CFLAGS += -mmcu=atmega328p
  AVRDUDE_TARGET = m328p
else ifeq ($(MCU),ATMEGA128A_TQFP64)
  CFLAGS += -DMCU_ATMEGA128A_TQFP64
  CFLAGS += -mmcu=atmega128a
  AVRDUDE_TARGET = m128
else ifeq ($(MCU),ATMEGA644P_DIP40)
  CFLAGS += -DMCU_ATMEGA644P_DIP40
  CFLAGS += -mmcu=atmega644p
  AVRDUDE_TARGET = m644p
else ifeq ($(MCU),ATMEGA164P_44)
  CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
  CFLAGS += -mmcu=atmega164p
  AVRDUDE_TARGET = m164p
else ifeq ($(MCU),ATMEGA324P_44)
  CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
  CFLAGS += -mmcu=atmega324p
  AVRDUDE_TARGET = m324p
else ifeq ($(MCU),ATMEGA644P_44)
  CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
  CFLAGS += -mmcu=atmega664p
  AVRDUDE_TARGET = m664p
else ifeq ($(MCU),ATMEGA164A_44)
  CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
  CFLAGS += -mmcu=atmega164a
  AVRDUDE_TARGET = m164pa
else ifeq ($(MCU),ATMEGA324A_44)
  CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
  CFLAGS += -mmcu=atmega324a
  AVRDUDE_TARGET = m324pa
else ifeq ($(MCU),ATMEGA644A_44)
  CFLAGS += -DMCU_ATMEGA164P_324P_644P_44
  CFLAGS += -mmcu=atmega664a
  AVRDUDE_TARGET = m664pa
else
  $(error "Incorrect MCU $(MCU) defined")
endif

ifdef F_CPU
  CFLAGS += -DF_CPU=$(F_CPU)
else
  $(error "No F_CPU defined for this board! Provide in board BSP (board.make), by Makefile or by command line (F_CPU=...)")
endif
