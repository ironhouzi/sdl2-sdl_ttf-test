SDL_LIB = `sdl2-config --libs` -lSDL2_ttf
SDL_INCLUDE = `sdl2-config --cflags`
LDFLAGS = -Wall -c $(SDL_INCLUDE)
BIN = sdl2-font_test

all: $(BIN)

$(BIN): sdl2_test.o
	gcc $< $(SDL_LIB) -o $@

sdl2_test.o: sdl2_test.c
	gcc $(LDFLAGS) $< -o $@
