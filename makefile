
CC=gcc
includeFlag=./i686-w64-mingw32/include/SDL2
libFlag=./i686-w64-mingw32/lib

bin/sdl: 
	${CC} src/*.c src/*.h -o bin/pong -I ${includeFlag} -L ${libFlag} -lmingw32 -lSDL2main -lSDL2
