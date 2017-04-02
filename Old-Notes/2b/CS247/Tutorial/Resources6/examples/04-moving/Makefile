CXX= g++
#CXXFLAGS = -g `/opt/local/bin/pkg-config gtkmm-2.4 --cflags --libs`
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags --libs`
OBJS = hidebuttons.o main.o
EXEC = hidebuttons

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXEC)

hidebuttons.o: hidebuttons.h hidebuttons.cc
main.o: hidebuttons.h main.cc


clean:
	rm -rf ${EXEC} ${OBJS}
