flash_default: all
ifndef COM
	$(error No COM port for programmer specified)
endif
	avrdude -F -v -p$(AVRDUDE_TARGET) -cwiring -P$(COM) -b115200 -D -Uflash:w:$(HEX_FILE):i
