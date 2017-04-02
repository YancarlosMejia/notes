CXX = g++
CXXFLAGS = -Wall -MMD
OBJECTS = SharedPointer.o Driver.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Pointers

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
