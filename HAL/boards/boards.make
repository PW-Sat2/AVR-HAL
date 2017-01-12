# -- BOARDS -------------------------------------

ifdef BOARD
BOARD_FOLDER = $(HAL_PATH)/boards/$(BOARD)

ifeq ("$(wildcard $(BOARD_FOLDER)/board.make)","")
BOARD_FOLDER = ./bsp/$(BOARD)
endif

$(info "Board $(BOARD) files imported from" $(BOARD_FOLDER));

ifeq ("$(wildcard $(BOARD_FOLDER)/board.make)","")
$(error "board.make not found!")
endif

include $(BOARD_FOLDER)/board.make
CFLAGS += -DBOARD=$(BOARD)
endif
