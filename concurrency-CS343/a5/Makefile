TYPE := EXT
UXX = `which u++`
CXXFLAGS = -g -multi -Wall -Wno-unused-label -O2 -DIMPLTYPE_"${TYPE}"
q3OBJECTS = q3main.o q3printer.o q3tallyVotes.o q3voter.o

all: vote

.SUFFIXES:
.SUFFIXES: .cc .o
.cc.o:
	$(UXX) $(CXXFLAGS) -c $< -o $@

-include ImplType

ifeq (${IMPLTYPE},${TYPE})
vote: $(q3OBJECTS)
	$(UXX) $(CXXFLAGS) $^ -o $@
else
ifeq (${TYPE},)
# set type to previous type
TYPE=${IMPLTYPE}
vote: $(q3OBJECTS)
	$(UXX) $(CXXFLAGS) $^ -o $@
else
.PHONY: vote
vote:
	rm -f ImplType
	touch q3tallyVotes.h
	sleep 1
	${MAKE} vote TYPE="${TYPE}"
endif
endif

ImplType:
	echo "IMPLTYPE=${TYPE}" > ImplType

q3tallyVotes.cc: q3tallyVotes_${TYPE}.cc
	cp q3tallyVotes_${TYPE}.cc q3tallyVotes.cc

q3main.o: q3main.cc q3tallyVotes.h q3printer.h q3voter.h
q3printer.o: q3printer.cc q3tallyVotes.h q3printer.h q3voter.h
q3tallyVotes.o: q3tallyVotes.cc q3tallyVotes.h q3printer.h q3voter.h
q3voter.o: q3voter.cc q3tallyVotes.h q3printer.h q3voter.h

clean:
	rm -f *.d
	rm -f *.o
	rm -f ImplType
	rm -f new
	rm -f vote
