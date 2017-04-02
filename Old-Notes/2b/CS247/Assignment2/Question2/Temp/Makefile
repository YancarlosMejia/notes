GTEST_DIR=~/coding/gtest
GTEST_FLAGS=-isystem $(GTEST_DIR)/include -pthread
GTEST_LIBS=$(GTEST_DIR)/lib/*
FILES=UserAccount.o Userid.o Password.o
ZIPPERS=UserAccount.cpp UserAccount.h Userid.cpp Userid.h Password.cpp Password.h Makefile

.SUFFIXES: 
.SUFFIXES: .o .cpp .h

.cpp.o:
	${CXX} -g -c $<

all: a2q2

test: a2q2_test

zip: a2q2_zip


a2q2: $(FILES) TestHarness.cpp
	${CXX} -g $(FILES) TestHarness.cpp -o Passwords

a2q2_test: a2q2 a2q2_test.cpp $(FILES)
	clear;
	clear;
	${CXX} $(GTEST_FLAGS) -g a2q2_test.cpp $(FILES) $(GTEST_LIBS) -o a2q2_test;
	./a2q2_test;

a2q2_zip: $(ZIPPERS)
	zip a2q2.zip $(ZIPPERS)


clean:
	rm -rf *.dSYM
	rm -rf *.zip
	rm -rf *.o
	rm -rf a2q2 a2q2_test
