# Inspiré des Makefile fournit lors des séances de TP
COMPILER=g++

CXXFLAGS += $(shell fltk-config --cxxflags | sed 's/-I/-isystem/g')
LDFLAGS  += $(shell fltk-config --ldflags)

CXXFLAGS += -std='c++20' -Wall -Wextra -Wsign-compare -pedantic -fmax-errors=2
LDFLAGS  += -lfltk

main: main.cpp block.o controller.o model.o view.o
	${COMPILER} ${CXXFLAGS} -o projet main.cpp block.o controller.o model.o view.o ${LDFLAGS}

%.o: %.cpp %.hpp
	${COMPILER} ${CXXFLAGS} -o $@ -c $< ${LDFLAGS}

.PHONY: clean
clean:
	-rm *.o
