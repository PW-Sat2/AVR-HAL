HAL_PATH = ../HAL
GTEST_DIR = gtest-1.7.0
CSRCS = 
TESTS = tests_run_all.cpp array_view.cpp array.cpp

INCLUDES = -I. -I$(HAL_PATH)/libs -I$(GTEST_DIR)/include/ -I$(GTEST_DIR)/include/gtest/

LIBS_FOLDERS = -L$(GTEST_DIR)/
GTEST_LIBS = $(GTEST_DIR)/libgtest.a
LIBS = -pthread -lgtest

CXX = g++ -std=gnu++1y
CXXFLAGS = -ggdb

PHONY= all test run clean

all: test run


$(GTEST_LIBS):
	wget http://googletest.googlecode.com/files/gtest-1.7.0.zip -O gtest.zip
	unzip -o gtest.zip
	rm gtest.zip
	cd gtest-1.7.0; cmake .
	make -C gtest-1.7.0

test: $(GTEST_LIBS) $(TESTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS_FOLDERS) $(GTEST_LIBS) $(SOURCES) $(TESTS) -o test $(LIBS)

run: test
	LD_LIBRARY_PATH=gtest-1.7.0/lib/.libs:$LD_LIBRARY_PATH  ./test
	rm -f test

clean:
	rm -f test
	rm -Rf gtest-1.7.0
	rm -f gtest.zip


