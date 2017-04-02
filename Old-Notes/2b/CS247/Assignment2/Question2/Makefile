FILES=UserAccount.o Userid.o Password.o

.SUFFIXES: 
.SUFFIXES: .o .cpp .h

.cpp.o:
	${CXX} -g -c $<

all: a2q2

a2q2: $(FILES) TestHarness.cpp
	${CXX} -g $(FILES) TestHarness.cpp -o Passwords

clean:
	rm -rf *.dSYM
	rm -rf *.zip
	rm -rf *.o
	rm -rf a2q2 a2q2_test
