CXX=g++
OBJECTS=Language.o English.o French.o Polish.o AbstractLanguageFactory.o Greeting.o main.o
SOURCE=$(OBJECTS:.o=.cc)
EXEC=greeting

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) -o $(EXEC) $(OBJECTS)

Language.o: Language.cc Language.h
	$(CXX) -c Language.cc

English.o: English.cc English.h Language.h
	$(CXX) -c English.cc

French.o: French.cc French.h Language.h
	$(CXX) -c French.cc

Polish.o: Polish.cc Polish.h Language.h
	$(CXX) -c Polish.cc

AbstractLanguageFactory.o: AbstractLanguageFactory.cc AbstractLanguageFactory.h Language.h English.h French.h Polish.h
	$(CXX) -c AbstractLanguageFactory.cc

Greeting.o: Greeting.cc Greeting.h AbstractLanguageFactory.h English.h Polish.h
	$(CXX) -c Greeting.cc

main.o: main.cc Greeting.h
	$(CXX) -c main.cc

clean:
	rm -rf $(OBJECTS) $(EXEC)