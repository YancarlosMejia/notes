# Standard flags
CXX = g++
CXXFLAGS = -g -Wall -MMD

OBJECTS = main.o KentuckyFriedChicken.o TacoBell.o PizzaHut.o YumRestaurantFactory.o YumRestaurant.o

EXEC = main

DEPENDS = ${OBJECTS:.o=.d} # substitute ".o" with ".d"

all : ${EXEC}

${EXEC} : ${OBJECTS}
	 ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
