CXX= g++
#CXXFLAGS = -g `/opt/local/bin/pkg-config gtkmm-2.4 --cflags --libs`
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS = -g `pkg-config gtkmm-2.4 --libs`
OBJS = hello.o
EXEC = hello


${EXEC}: ${OBJS}
	$(CXX) ${OBJS} $(LDFLAGS) -o ${EXEC}


hello.o: hello.cc


clean:
	rm -rf ${EXEC} ${OBJS}
