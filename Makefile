SDL_LIB = -L/usr/lib64 -Wl,-rpath,/usr/lib64 -lSDL2 -lpthread -lSDL_ttf
SDL_INCLUDE = -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS = -Wall -c $(SDL_INCLUDE)
BIN = sdl2-font_test

all: $(BIN)

$(BIN): sdl2_test.o
	gcc $< $(SDL_LIB) -o $@

sdl2_test.o: sdl2_test.c
	gcc $(LDFLAGS) $< -o $@
