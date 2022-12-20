# Inspiré des Makefile fournit lors des séances de TPs
COMPILER=g++

CXXFLAGS += $(shell fltk-config --cxxflags | sed 's/-I/-isystem/g')
LDFLAGS  += $(shell fltk-config --ldflags)

CXXFLAGS += -std='c++20' -Wall -Wextra -Wsign-compare -pedantic -fmax-errors=2 -Werror=all
LDFLAGS  += -lfltk

OBJ=point.o block.o player.o controller.o model.o view.o animation.o

main: main.cpp constants.hpp ${OBJ}
	${COMPILER} ${CXXFLAGS} -o projet main.cpp ${OBJ} ${LDFLAGS}

%.o: %.cpp %.hpp
	$(info ************)
	$(info ** Compiling $(@) $(<))
	$(info ************)
	${COMPILER} ${CXXFLAGS} -o $@ -c $< ${LDFLAGS}

.PHONY: clean
clean:
	-rm *.o
