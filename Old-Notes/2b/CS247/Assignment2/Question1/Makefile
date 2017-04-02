GTEST_DIR=~/coding/gtest
GTEST_FLAGS=-isystem $(GTEST_DIR)/include -pthread
GTEST_LIBS=$(GTEST_DIR)/lib/*


.SUFFIXES: 
.SUFFIXES: .o .cpp .h

.cpp.o:
	${CXX} -g -c $<


all: a2q1

test: a2q1_test

zip: a2q1_zip


a2q1: Date.o DateTestHarness.cpp
	${CXX} -g Date.o DateTestHarness.cpp -o a2q1

a2q1_test: a2q1 date_test.cpp Date.o
	clear;
	${CXX} $(GTEST_FLAGS) -g date_test.cpp Date.o $(GTEST_LIBS) -o a2q1_test;
	./a2q1_test;

a2q1_zip: Date.cpp Date.h
	zip a2q1.zip Date.cpp Date.h


clean:
	rm -rf *.dSYM
	rm -rf *.zip
	rm -rf *.o
	rm -rf a2q1 a2q1_test
