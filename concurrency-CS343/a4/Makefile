KIND:=STACK
TYPE:=MC

UXX=`which u++`
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD -O2 -multi -nodebug -D"${KIND}" -DIMPLTYPE_"${TYPE}"

q2: tallyVotes


.SUFFIXES:
.SUFFIXES: .cc .o

.cc.o:
	$(UXX) $(CXXFLAGS) -c $< -o $@


-include ImplType

q2tallyVotes.o: q2tallyVotes.cc q2tallyVotes.h
ifeq (${IMPLTYPE},${TYPE})
tallyVotes: q2tallyVotes.o
	$(UXX) $(CXXFLAGS) $^ -o $@
else
ifeq (${TYPE},)
TYPE=${IMPLTYPE}
tallyVotes: q2tallyVotes.o
	$(UXX) $(CXXFLAGS) $^ -o $@
else
.PHONY: tallyVotes
tallyVotes:
	rm -f ImplType
	touch q2tallyVotes.h
	sleep 1
	${MAKE} TYPE="${TYPE}" SENTINEL="${SENTINEL}"
endif
endif

ImplType:
	echo "IMPLTYPE=${TYPE}" > ImplType


clean:
	rm -f *.d
	rm -f *.o
	rm -f ImplKind
	rm -f ImplType
	rm -f tallyVotes
