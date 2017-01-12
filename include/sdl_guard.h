//
//  sdl.h
//  Learn SDL
//
//  Created by Jordan Osborn on 16/10/2016.
//  Copyright © 2016 Jordan Osborn. All rights reserved.
//

#ifndef sdl_h
#define sdl_h
    #ifdef __APPLE__
        #include <SDL2/SDL.h>
    #elifdef __WIN32
        #include <SDL/SDL.h>
    #else
        #include <SDL2/SDL.h>
    #endif

#endif /* sdl_h */
