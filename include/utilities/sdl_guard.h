#ifndef sdl_h
#define sdl_h
    #ifdef __APPLE__
        #include <SDL2/SDL.h>
    #elif __WIN32
        #include <SDL/SDL.h>
    #else
        #include <SDL2/SDL.h>
    #endif

#endif /* sdl_h */
