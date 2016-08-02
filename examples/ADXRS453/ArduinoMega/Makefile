# -- User definitions ---------------------------

HAL_PATH = ../../../HAL
APP_NAME = ADXRS453


BOARD = ARDUINOMEGA2560

INCLUDES = \
  -I .

SRCS = \
  ADXRS453.cpp

include $(HAL_PATH)/build.make
LINKER_FLAGS += -Wl,-u,vfprintf -lprintf_flt -lm
