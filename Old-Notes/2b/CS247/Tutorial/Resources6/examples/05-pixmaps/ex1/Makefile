CXX= g++
#CXXFLAGS = -g `/opt/local/bin/pkg-config gtkmm-2.4 --cflags --libs`
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags --libs`
OBJS1 = helloworld.o main.o
EXEC1 = hello

$(EXEC1): $(OBJS1)
	$(CXX) $(OBJS1) $(CXXFLAGS) -o $(EXEC1)

helloworld.o: helloworld.h helloworld.cc
main.o: helloworld.h main.cc

clean:
	rm -rf ${EXEC1} ${OBJS1}
