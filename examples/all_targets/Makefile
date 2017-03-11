all: ARDUINOMEGA2560 ARDUINONANO328P EASYAVR128 EVB_ATMEGA324P EVB_MEGA644P

build-ARDUINOMEGA2560:
	mkdir $@
	
ARDUINOMEGA2560: build-ARDUINOMEGA2560
	cmake -Bbuild-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C build-$@ -j5


build-ARDUINONANO328P:
	mkdir $@
ARDUINONANO328P: build-ARDUINONANO328P
	cmake -Bbuild-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C build-$@ -j5


build-EASYAVR128:
	mkdir $@
EASYAVR128: build-EASYAVR128
	cmake -Bbuild-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C build-$@ -j5


build-EVB_ATMEGA324P:
	mkdir $@
EVB_ATMEGA324P: build-EVB_ATMEGA324P
	cmake -Bbuild-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C build-$@ -j5


build-EVB_MEGA644P:
	mkdir $@
EVB_MEGA644P: build-EVB_MEGA644P
	cmake -Bbuild-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C build-$@ -j5

clean:
	rm -rf build-*