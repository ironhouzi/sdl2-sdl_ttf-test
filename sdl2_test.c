#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include <SDL2/SDL.h>
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

    if(TTF_Init() == -1) {
        printf("Error loading TTF_Init()!\n%s\n", TTF_GetError());
        SDL_Quit();
        exit(2);
    }

    printf("%s\n", argv[1]);
    TTF_Font *font;
    font = TTF_OpenFont(argv[1], 30);

    if(!font) {
        printf("%s\n", TTF_GetError());
        return 1;
    }

    setlocale(LC_ALL, "");
    wchar_t tibstring[] = { 0x0f56, 0x0f66, 0x0f90, 0x0fb1, 0x0f7c, 0x0f44, 0x0f66 };
    printf("%ls\n", tibstring);

    SDL_Quit();
    return 0;
}
