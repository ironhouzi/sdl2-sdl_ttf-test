#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, const char *argv[])
{
    if(argc != 2) {
        printf("%s takes .ttf file as argument.\n", argv[0]);
        return 1;
    }

    SDL_version compile_version;
    const SDL_version *link_version=TTF_Linked_Version();
    SDL_TTF_VERSION(&compile_version);
    printf("compiled with SDL_ttf version: %d.%d.%d\n",
            compile_version.major,
            compile_version.minor,
            compile_version.patch);
    printf("running with SDL_ttf version: %d.%d.%d\n",
            link_version->major,
            link_version->minor,
            link_version->patch);

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error with import!\n");
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow( "TTF Test",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        800,
                                        600,
                                        SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(win,
                                                -1,
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);

    if(TTF_Init() == -1) {
        printf("Error loading TTF_Init()!\n%s\n", TTF_GetError());
        SDL_Quit();
        exit(2);
    }

    TTF_Font *font;
    /* MS Himalaya (himalaya.ttf): http://fontzone.net/font-details/microsoft-himalaya */
    font = TTF_OpenFont(argv[1], 600);

    if(!font) {
        printf("%s\n", TTF_GetError());
        return 1;
    }

    const char tibstring[] = {  0xe0, 0xbd, 0x96,
                                0xe0, 0xbd, 0xa6,
                                0xe0, 0xbe, 0x90,
                                0xe0, 0xbe, 0xb1,
                                0xe0, 0xbd, 0xbc,
                                0xe0, 0xbd, 0x84,
                                0xe0, 0xbd, 0xa6 };

    SDL_Color colour = { 255, 255, 255, 255 };
    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, tibstring, colour);

    if(surface == NULL) {
        TTF_CloseFont(font);
        printf("Surface error!\n");
        return 0;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Event event;
    int quit = 0;

    while (!quit) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = 1;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_Quit();

    return 0;
}
