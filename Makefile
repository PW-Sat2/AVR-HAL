LINTER_PARAMS=--extensions=hpp,cpp,h,c --filter=-legal/copyright,-build/include,-runtime/arrays,-runtime/references,-build/c++11,-build/namespaces,-runtime/explicit,-runtime/printf,-runtime/int,-build/header_guard --linelength=120

all: checkStyle examples unit_tests_run

clean:
	rm -Rvf tmp
	make -C examples clean
	rm -rf unit_tests/build

tmp:
	mkdir -p tmp

tmp/cpplint.py: tmp
	wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py -O tmp/cpplint.py

checkStyle: tmp/cpplint.py
	find . -type f \( -name "*.cpp" -o -name "*.h" \) | grep -v "hal/libs/std/"  | grep -v "unit_tests/build" | xargs python tmp/cpplint.py $(LINTER_PARAMS)

examples: force
	make -C examples

unit_tests_run: force
	cd unit_tests; mkdir build; cd build; cmake ..
	make -C unit_tests/build unit_tests -j5
	make -C unit_tests/build unit_tests.sim | tee unit_tests/build/out
	if grep -q "FAIL" unit_tests/build/out; then exit 1; fi
	@echo "Success!"


force:

