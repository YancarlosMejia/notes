CXX = g++
CXXFLAGS = -Wall -MMD -g
OBJS = Inventory.o Pasta.o Penne.o PenneFactory.o Ravioli.o RavioliFactory.o Rigatoni.o RigatoniFactory.o main.o
DEPENDS = ${OBJS:.o=.d}
EXEC = pattern

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm -rf ${DEPENDS} ${OBJS} ${EXEC}

-include ${DEPENDS}