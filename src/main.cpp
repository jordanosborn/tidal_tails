// C++ Headers
#include <string>
#include <iostream>
#include <fstream>

// OpenGL / glew / SDL Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include "sdl_guard.h"

// GSL Headers
//#include <gsl/gsl_errno.h>
//#include <gsl/gsl_odeiv.h>

// Headers
#include "physics/universe.h"
#include "physics/particle.h"
#include "capture/screenshot.h"
#include "utilities/utilities.h"


std::string PROGRAMNAME = "Tidal Tails";
GLint WIDTH = 900;
GLint HEIGHT = 900;

GLdouble t = 0;

// SDL_Window
SDL_Window *mainWindow;

// openGL context
SDL_GLContext mainContext;

bool set_openGL_attributes();
void check_SDL_error(int line);
void run_simulation();
void cleanup();

bool Init() {
    // Initialize SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to init SDL\n";
        return false;
    }

    mainWindow = SDL_CreateWindow(PROGRAMNAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    // SDL error check
    if (!mainWindow) {
        std::cout << "Unable to create window\n";
        check_SDL_error(__LINE__);
        return false;
    }

    // Create openGL context
    mainContext = SDL_GL_CreateContext(mainWindow);

    set_openGL_attributes();

    // Buffer swap synchronized with monitor's vertical refresh rate
    SDL_GL_SetSwapInterval(1);

    // Init GLEW macOS
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    return true;
}

bool set_openGL_attributes() {
    // USe GLCore
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Use OpenGL 3.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return true;
}

int main(int argc, char *argv[]) {

    if (!Init()) return -1;

    glClearColor(0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mainWindow);
    run_simulation();

    cleanup();

    return 0;
}

void run_simulation() {
    universe universe1 = universe();
    universe1.generate_universe();
    GLboolean loop = true;
    GLboolean paused = true;
    GLboolean logging = false;
    GLboolean reversed = false;

    while (loop == true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) loop = false;

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                    case SDLK_p:
                        screenshot("screenshot."+ format_time(t)+".tga");
                        std::cout << "Screenshot created." << std::endl;
                        break;
                    case SDLK_SPACE:
                        paused = not paused;
                        std::cout << "Pause status: " << static_cast<int>(paused) << std::endl;
                        break;
                    case SDLK_x:
                        paused = true;
                        //apply step forward
                        std::cout << "Forward time step applied." << std::endl;
                    case SDLK_z:
                        paused = true;
                        //apply step back
                        std::cout << "Backward time step applied." << std::endl;
                    case SDLK_r:
                        reversed= not reversed;
                        //reverse time
                        std::cout << "Time reversed." << std::endl;
                    case SDLK_l:
                        logging = not logging;
                        //start/stop logging
                        std::cout << "Logging status: " << static_cast<int>(logging)  << std::endl;
                    case SDLK_w:
                        //pan up
                    case SDLK_a:
                        //pan down
                    case SDLK_s:
                        //pan left
                    case SDLK_d:
                        //pan right
                    case SDLK_q:
                        //zoom out
                    case SDLK_e:
                        //zoom in

                    default:
                        break;
                }
            }
        }
        if(!paused) {
            universe1.update(mainWindow, reversed);
            t += getTimestep(&universe1);
        }
        if(logging){

        }

    }
}

void cleanup() {
    // Delete OpengL context
    SDL_GL_DeleteContext(mainContext);

    // Destroy window
    SDL_DestroyWindow(mainWindow);

    // Shutdown SDL2
    SDL_Quit();
}

void check_SDL_error(GLint line = -1) {
    std::string error = SDL_GetError();

    if (error != "") {
        std::cout << "SLD Error : " << error << std::endl;

        if (line != -1) std::cout << "\nLine : " << line << std::endl;

        SDL_ClearError();
    }
}

