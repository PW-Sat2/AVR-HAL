LINTER_PARAMS=--root=AVR-HAL --extensions=hpp,cpp,h,c --filter=-legal/copyright,-build/include,-runtime/arrays,-runtime/references,-build/c++11,-build/namespaces,-runtime/explicit,-runtime/printf,-runtime/int --linelength=150

SOURCES := $(shell find . -type f \( -name "*.cpp" -o -name "*.h" \) | grep -v "cmake-build")

all: unit_tests_run examples SingleDeviceTests checkFormat checkStyle
.PHONY: clean checkStyle format checkFormat examples unit_tests_run SingleDeviceTests

clean:
	make -C examples clean
	rm -rf unit_tests/cmake-build
	rm -rf tests/SingleDevice/cmake-build

checkStyle:
	@cpplint $(LINTER_PARAMS) $(SOURCES)

format:
	@clang-format-5.0 -i $(SOURCES)

checkFormat:
	@! clang-format-5.0 $(SOURCES) -output-replacements-xml | grep -c "<replacement " >/dev/null
	@echo "Format OK"

examples:
	make -C examples

unit_tests_run:
	cd unit_tests; mkdir cmake-build; cd cmake-build; cmake ..
	make -C unit_tests/cmake-build unit_tests.run -j5
	@echo "Success!"

SingleDeviceTests:
	cd tests/SingleDevice; mkdir cmake-build; cd cmake-build; cmake ..
	make -C tests/SingleDevice/cmake-build -j5
