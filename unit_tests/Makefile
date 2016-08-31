HAL_PATH = ../HAL
GTEST_DIR = googletest-release-1.7.0
CSRCS = 
TESTS = tests_run_all.cpp I2C.cpp array_view.cpp array.cpp bit_operations.cpp compile_time.cpp

INCLUDES = -I. -I$(HAL_PATH)/libs -I$(GTEST_DIR)/include/ -I$(GTEST_DIR)/include/gtest/ -I$(HAL_PATH)/periph

LIBS_FOLDERS = -L$(GTEST_DIR)/
GTEST_LIBS = $(GTEST_DIR)/libgtest.a
LIBS = -pthread -lgtest

CXX = g++ -std=gnu++1y
CXXFLAGS = -ggdb

PHONY= all test run clean

all: test run


$(GTEST_LIBS):
	wget https://github.com/google/googletest/archive/release-1.7.0.zip -O gtest.zip
	unzip -o gtest.zip
	rm gtest.zip
	cd $(GTEST_DIR); cmake .
	make -C $(GTEST_DIR)

test: $(GTEST_LIBS) $(TESTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS_FOLDERS) $(GTEST_LIBS) $(SOURCES) $(TESTS) -o test $(LIBS)

run: test
	LD_LIBRARY_PATH=$(GTEST_DIR)/lib/.libs:$LD_LIBRARY_PATH  ./test
	rm -f test

clean:
	rm -f test
	rm -Rf $(GTEST_DIR)
	rm -f gtest.zip


