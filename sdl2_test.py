import sys
import struct
import ctypes

try:
    from sdl2 import *
    import sdl2.ext as sdl2ext
    import sdl2.sdlttf as sdlttf
except ImportError:
    import traceback
    traceback.print_exc()
    sys.exit(1)


def run():
    sdl2ext.init()
    sdlttf.TTF_Init(SDL_INIT_EVERYTHING)

    font = sdlttf.TTF_OpenFont(str.encode("himalaya.ttf"), 300)
    flags = SDL_WINDOW_SHOWN
    color = sdlttf.SDL_Color(255, 255, 255, 255)
    tibstring = 'བསྐྱོངས་'
    sdlstr = (ctypes.c_uint16 * len(tibstring))(*map(ord, tibstring))

    window = SDL_CreateWindow(b'TTF TEST',
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800,
                              600,
                              flags)

    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC)

    # message = sdlttf.TTF_RenderUTF8_Blended(font,
    #                                         str.encode(tibstring),
    #                                         color)

    message = sdlttf.TTF_RenderUNICODE_Blended(
        font,
        sdlstr,
        color)

    tex = SDL_CreateTextureFromSurface(renderer, message)
    dst = SDL_Rect(0, 0, 640, 480)

    SDL_RenderCopy(renderer, tex, None, dst)
    SDL_ShowWindow(window)

    running = True

    while running:
        events = sdl2ext.get_events()

        for event in events:
            if event.type == SDL_QUIT:
                running = False
                break

        SDL_RenderPresent(renderer)

    return 0

if __name__ == "__main__":
    sys.exit(run())
