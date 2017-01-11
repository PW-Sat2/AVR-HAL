flash_default: all
ifndef COM
	$(error No COM port for programmer specified)
endif
	avrdude -v -p$(AVRDUDE_TARGET) -carduino -b9600 -P$(COM) -D -Uflash:w:$(HEX_FILE):i 