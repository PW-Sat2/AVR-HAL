all: all_targets

all_targets: force
	make -C all_targets

easyAVR128: force
	make -C easyAVR128

clean:
	make -C all_targets clean
	make -C easyAVR128 clean

force: