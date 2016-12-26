flash_default: all
	avrdude -v -p$(AVRDUDE_TARGET) -cusbasp -D -Uflash:w:$(HEX_FILE):i