all: EASYAVR128

build:
	mkdir $@
EASYAVR128: build
	cmake -Bbuild -H. -G "Unix Makefiles"
	make -C build -j5



clean:
	rm -rf build