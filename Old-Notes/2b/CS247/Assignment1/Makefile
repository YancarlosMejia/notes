GTEST_DIR=~/coding/gtest
GTEST_LIBS=$(GTEST_DIR)/lib/*
GTEST_FLAGS=-isystem $(GTEST_DIR)/include -pthread

all: a1q1 a1q2

test: a1q1_test a1q2_test

a1q1: AccountTestHarness.cpp
	${CXX} -g AccountTestHarness.cpp -o a1q1

a1q1_test: a1q1 a1q1_test.cpp
	${CXX} $(GTEST_FLAGS) -g a1q1_test.cpp $(GTEST_LIBS) -o a1q1_test;
	./a1q1_test;

a1q2: DynListTestHarness.cpp
	${CXX} -g DynListTestHarness.cpp -o a1q2

a1q2_test: a1q2 a1q2_test.cpp
	${CXX} $(GTEST_FLAGS) -g a1q2_test.cpp $(GTEST_LIBS) -o a1q2_test;
	./a1q2_test

clean:
	rm -rf a1q1 a1q2 a1q1_test a1q2_test *.dSYM *.zip
