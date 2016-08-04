
LINTER_PARAMS=--extensions=hpp,cpp,h,c --filter=-legal/copyright,-build/include,-runtime/arrays --linelength=120

all: checkStyle cppcheck flawFinder
.PHONY: all clean tmp checkStyle cppcheck flawFinder

clean:
	rm -Rvf tmp

tmp:
	mkdir -p tmp

tmp/cpplint.py:
	wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py -O tmp/cpplint.py

checkStyle: tmp tmp/cpplint.py	
	find . -type f \( -name "*.cpp" -o -name "*.h" \) | grep -v "unit_tests/gtest-" | grep -v "HAL/libs/type_traits.h" | xargs python tmp/cpplint.py $(LINTER_PARAMS)

cppcheck:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) | grep -v "unit_tests/gtest-" | grep -v "HAL/libs/type_traits.h" | xargs cppcheck --enable=all --inconclusive --std=c++11

tmp/flawfinder:
	wget http://www.dwheeler.com/flawfinder/flawfinder-1.31.tar.gz -O tmp/flawFinder.tar.gz
	tar xvzf tmp/flawFinder.tar.gz flawfinder-1.31/flawfinder
	mv flawfinder-1.31/flawfinder tmp/flawfinder
	rmdir flawfinder-1.31

flawFinder: tmp tmp/flawfinder
	./tmp/flawfinder ./
