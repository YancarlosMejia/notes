CXX= g++
#CXXFLAGS = -g `/opt/local/bin/pkg-config gtkmm-2.4 --cflags --libs`
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags --libs`
OBJS2 = DeckGUI.o otherworld.o driver.o
EXEC2 = other

$(EXEC2): $(OBJS2)
	$(CXX) $(OBJS2) $(CXXFLAGS) -o $(EXEC2)

DeckGUI.o: DeckGUI.h DeckGUI.cc
otherworld.o: otherworld.h otherworld.cc
driver.o: otherworld.h driver.cc

clean:
	rm ${OBJS2} ${EXEC2}
