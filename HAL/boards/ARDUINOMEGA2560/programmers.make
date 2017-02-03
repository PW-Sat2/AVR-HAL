flash_default: all
ifndef COM
	$(error No COM port for programmer specified)
endif
	avrdude -v -p$(AVRDUDE_TARGET) -cwiring -P$(COM) -b115200 -D -Uflash:w:$(HEX_FILE):i
