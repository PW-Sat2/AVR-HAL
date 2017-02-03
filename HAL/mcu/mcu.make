includes.ATMEGA2560_TQFP100       := atmega2560_tqfp100
mmcutarget.ATMEGA2560_TQFP100     := atmega2560
avrdudetarget.ATMEGA2560_TQFP100  := atmega2560

includes.ATMEGA328P_TQFP32        := atmega328p_tqfp32
mmcutarget.ATMEGA328P_TQFP32      := atmega328p
avrdudetarget.ATMEGA328P_TQFP32   := m328p

includes.ATMEGA128A_TQFP64        := atmega128a_tqfp64
mmcutarget.ATMEGA128A_TQFP64      := atmega128a
avrdudetarget.ATMEGA128A_TQFP64   := m128

includes.ATMEGA644P_DIP40         := atmega644p_dip40
mmcutarget.ATMEGA644P_DIP40       := atmega644p
avrdudetarget.ATMEGA644P_DIP40    := m644p

includes.ATMEGA164P_44            := atmega164p_324p_644p_44
mmcutarget.ATMEGA164P_44          := atmega164p
avrdudetarget.ATMEGA164P_44       := m164p

includes.ATMEGA164A_44            := atmega164p_324p_644p_44
mmcutarget.ATMEGA164P_44          := atmega164a
avrdudetarget.ATMEGA164P_44       := m164pa

includes.ATMEGA324P_44            := atmega164p_324p_644p_44
mmcutarget.ATMEGA324P_44          := atmega324p
avrdudetarget.ATMEGA324P_44       := m324p

includes.ATMEGA324P_44            := atmega164p_324p_644p_44
mmcutarget.ATMEGA324P_44          := atmega324a
avrdudetarget.ATMEGA324P_44       := m324pa

includes.ATMEGA644P_44            := atmega164p_324p_644p_44
mmcutarget.ATMEGA644P_44          := atmega664p
avrdudetarget.ATMEGA644P_44       := m664p

includes.ATMEGA644A_44            := atmega164p_324p_644p_44
mmcutarget.ATMEGA644P_44          := atmega664a
avrdudetarget.ATMEGA644P_44       := m664pa


INCLUDES += -I$(HAL_PATH)/mcu/${includes.${MCU}}
CFLAGS += -mmcu=${mmcutarget.${MCU}}
AVRDUDE_TARGET = ${avrdudetarget.${MCU}}

ifeq (${includes.${MCU}},)
  $(error "Incorrect MCU $(MCU) defined")
endif

ifdef F_CPU
  CFLAGS += -DF_CPU=$(F_CPU)
else
  $(error "No F_CPU defined for this board! Provide in board BSP (board.make), by Makefile or by command line (F_CPU=...)")
endif
