flash_default: all
ifndef COM
	$(error No COM port for programmer specified)
endif
	avrdude -v -p$(AVRDUDE_TARGET) -carduino -P$(COM) -b57600 -D -Uflash:w:$(HEX_FILE):i -vvvv