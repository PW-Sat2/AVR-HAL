
LINTER_PARAMS=--extensions=hpp,cpp,h,c --filter=-legal/copyright

all: checkStyle cppcheck flawFinder

clean:
	rm -Rvf tmp
tmp:
	mkdir tmp
tmp/cpplint.py: tmp
	wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py -O tmp/cpplint.py
checkStyle: tmp/cpplint.py	
	find . -type f \( -name "*.cpp" -o -name "*.h" \) | xargs python2 tmp/cpplint.py $(LINTER_PARAMS)
cppcheck:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) | xargs cppcheck --enable=all --inconclusive --std=c++11
tmp/flawfinder-1.31/flawfinder: tmp
	wget http://www.dwheeler.com/flawfinder/flawfinder-1.31.tar.gz -O tmp/flawFinder.tar.gz
	tar xvzf tmp/flawFinder.tar.gz flawfinder-1.31/flawfinder
	mv flawfinder-1.31 tmp/
flawFinder: tmp/flawfinder-1.31/flawfinder
	tmp/flawfinder-1.31/flawfinder HAL
