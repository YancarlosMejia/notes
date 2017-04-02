CXX=g++
OBJECTS=Cat.o Dog.o Fox.o CatFactory.o DogFactory.o FoxFactory.o main.o
SOURCE=$(OBJECTS:.o=.cpp)
EXEC=exec

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) -o $(EXEC) $(OBJECTS)

Sound.o: Sound.cpp Sound.h
	$(CXX) -c Sound.cpp Sound.h

Dog.o: Dog.cpp Dog.h
	$(CXX) -c Dog.cpp Dog.h

Cat.o: Cat.cpp Cat.h
	$(CXX) -c Cat.cpp Cat.h

Fox.o: Fox.cpp Fox.h
	$(CXX) -c Fox.cpp Fox.h

DogFactory.o: DogFactory.cpp DogFactory.h
	$(CXX) -c DogFactory.cpp DogFactory.h

CatFactory.o: CatFactory.cpp CatFactory.h
	$(CXX) -c CatFactory.cpp CatFactory.h

FoxFactory.o: FoxFactory.cpp FoxFactory.h
	$(CXX) -c FoxFactory.cpp FoxFactory.h

Main.o: main.cpp
	$(CXX) -c main.cpp
