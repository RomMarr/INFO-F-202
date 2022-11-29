# Inspiré des Makefile fournit lors des séances de TP
COMPILER=g++

# -lfltk_images 
# -lfltk_images -lpng -lz -ljpeg -lfltk_gl -lfltk 
CXXFLAGS += -std='c++20' -Wall -Wextra -Wsign-compare -pedantic -fmax-errors=2
# LDXFLAGS += -lfltk_images

# --use-images 
CXXFLAGS += $(shell fltk-config --cxxflags | sed 's/-I/-isystem/g')

# Idea for pkg-config https://github.com/Rangi42/tilemap-studio/blob/69b1d9aa985c4b083294aa25cb0dc59ed5e44065/Makefile#L18
LDFLAGS  += $(shell fltk-config --ldflags) # $(shell pkg-config --libs libpng xpm)

main: main.cpp game.o block.o controller.o model.o view.o
	${COMPILER} ${CXXFLAGS}  -o projet main.cpp game.o block.o controller.o model.o view.o ${LDFLAGS}

%.o: %.cpp %.hpp
	${COMPILER} ${CXXFLAGS} -o $@ -c $< ${LDFLAGS}

.PHONY: clean
clean:
	-rm *.o
