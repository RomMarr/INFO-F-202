# Inspiré des Makefile fournit lors des séances de TP
COMPILER=g++

CXXFLAGS += $(shell fltk-config --cxxflags | sed 's/-I/-isystem/g')
LDFLAGS  += $(shell fltk-config --ldflags)

CXXFLAGS += -std='c++20' -Wall -Wextra -Wsign-compare -pedantic -fmax-errors=2
LDFLAGS  += -lfltk

main: main.cpp game.o bloc.o drawable.o
	${COMPILER} ${CXXFLAGS}  -o projet main.cpp game.o bloc.o drawable.o ${LDFLAGS}

game.o: game.cpp game.h
	${COMPILER} ${CXXFLAGS} -c game.cpp ${LDFLAGS}

bloc.o: bloc.cpp bloc.h
	${COMPILER} ${CXXFLAGS} -c bloc.cpp ${LDFLAGS}

drawable.o: drawable.cpp drawable.h
	${COMPILER} ${CXXFLAGS} -c drawable.cpp ${LDFLAGS}

.PHONY: clean
clean:
	-rm *.o