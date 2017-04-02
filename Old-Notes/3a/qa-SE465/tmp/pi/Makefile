SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.bc)

CXX=`which g++`
LINK=`which llvm-link`

FLAGS=

TARGET=program


all: $(TARGET)

debug: FLAGS+=-g -Wall -DDEBUG
debug: all


$(TARGET): $(TARGET).bc
	$(CXX) $(FLAGS) $< -o $@

$(TARGET).bc: $(OBJ)
	$(LINK) -v $(OBJ) -o $@

%.bc: %.cpp
	$(CXX) $(FLAGS) -emit-llvm -c $< -o $@


test: debug
	./verify.sh

clean:
	rm -f *.bc
	rm -f call_graph
	rm -f $(TARGET)
	rm -f $(TARGET)_*_*.err
	rm -f $(TARGET)_*_*.out
	rm -f test*/call_graph
	./clean.sh
