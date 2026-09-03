# GNU compiler
CC=gcc

ifeq ($(OS), Windows_NT)

	# path to SDL2 headers
	includeSDL2= -I ./sdl2/include -I ./sdl2/include/SDL2
	# path to SDL2 libraies
	libSDL2= -L ./sdl2/lib -lmingw32 -lSDL2main -lSDL2
else 
	# Linux build with system SDL2 (or sdl2-compat)
	# -lm = add math.h lib
    includeSDL2 := $(shell pkg-config --cflags sdl2) -I /usr/include
    libSDL2 := $(shell pkg-config --libs sdl2) -lm
endif

bin/pong: 
	${CC} src/*.c src/*.h -o bin/pong ${includeSDL2} ${libSDL2} -Wall
