# -- BOARDS -------------------------------------

BOARD_FOLDER = $(HAL_PATH)/boards/$(BOARD)

ifeq ("$(wildcard $(BOARD_FOLDER)/board.make)","")
  $(info "Board not found in HAL: $(BOARD_FOLDER)/board.make");
  BOARD_FOLDER = ./bsp/$(BOARD)
endif

ifeq ("$(wildcard $(BOARD_FOLDER)/board.make)","")
  $(error "board.make not found!")
endif

$(info "Board $(BOARD) files imported from" $(BOARD_FOLDER));

include $(BOARD_FOLDER)/board.make
INCLUDES += -I$(BOARD_FOLDER)
