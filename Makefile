LINTER_PARAMS=--extensions=hpp,cpp,h,c --filter=-legal/copyright,-build/include,-runtime/arrays,-runtime/references,-build/c++11,-build/namespaces,-runtime/explicit,-runtime/printf,-runtime/int --linelength=120

all: checkFormat checkStyle examples unit_tests_run SingleDeviceTests

clean:
	rm -Rvf tmp
	make -C examples clean
	rm -rf unit_tests/build

tmp:
	mkdir -p tmp

tmp/cpplint.py: tmp
	wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py -O tmp/cpplint.py

checkStyle: tmp/cpplint.py
	find . -type f \( -name "*.cpp" -o -name "*.h" \) | grep -v "hal/libs/std/"  | grep -v "/build/" | grep -v "/cmake-build-debug/" | xargs python tmp/cpplint.py $(LINTER_PARAMS)

format:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) | grep -v "hal/libs/std/"  | grep -v "/build/" | grep -v "/cmake-build-debug/" | xargs clang-format -i

checkFormat: format
	git diff --exit-code

examples: force
	make -C examples

unit_tests_run: force
	cd unit_tests; mkdir build; cd build; cmake ..
	make -C unit_tests/build unit_tests.run -j5
	@echo "Success!"

SingleDeviceTests:
	cd tests/SingleDevice; mkdir build; cd build; cmake ..
	make -C tests/SingleDevice/build -j5

force:

