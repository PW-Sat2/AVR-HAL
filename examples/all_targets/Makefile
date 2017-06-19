all: ARDUINOMEGA2560 ARDUINONANO328P EASYAVR128 EVB_ATMEGA324P EVB_MEGA644P

cmake-build-ARDUINOMEGA2560:
	mkdir $@
ARDUINOMEGA2560: cmake-build-ARDUINOMEGA2560
	cmake -Bcmake-build-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C cmake-build-$@ -j5


cmake-build-ARDUINONANO328P:
	mkdir $@
ARDUINONANO328P: cmake-build-ARDUINONANO328P
	cmake -Bcmake-build-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C cmake-build-$@ -j5


cmake-build-EASYAVR128:
	mkdir $@
EASYAVR128: cmake-build-EASYAVR128
	cmake -Bcmake-build-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C cmake-build-$@ -j5


cmake-build-EVB_ATMEGA324P:
	mkdir $@
EVB_ATMEGA324P: cmake-build-EVB_ATMEGA324P
	cmake -Bcmake-build-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C cmake-build-$@ -j5


cmake-build-EVB_MEGA644P:
	mkdir $@
EVB_MEGA644P: cmake-build-EVB_MEGA644P
	cmake -Bcmake-build-$@ -H. -G "Unix Makefiles" -DBOARD=$@
	make -C cmake-build-$@ -j5

clean:
	rm -rf cmake-build-*