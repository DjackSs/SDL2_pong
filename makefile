
# GNU compiler
CC=gcc

# path to SDL2 headers
includeSDL2=./i686-w64-mingw32/include/SDL2

# path to SDL2 libraies
libSDL2=./i686-w64-mingw32/lib

bin/sdl: 
	${CC} src/*.c src/*.h -o bin/pong -I ${includeSDL2} -L ${libSDL2} -lmingw32 -lSDL2main -lSDL2
