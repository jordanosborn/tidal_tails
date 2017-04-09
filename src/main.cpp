// C++ Headers
#include <string>
#include <iostream>
#include <fstream>

// OpenGL / glew / SDL Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include "utilities/sdl_guard.h"

// GSL Headers
//#include <gsl/gsl_errno.h>
//#include <gsl/gsl_odeiv.h>

// Headers
#include "physics/universe.h"
#include "physics/particle.h"
#include "capture/screenshot.h"
#include "utilities/utilities.h"
#include "utilities/camera.h"


std::string PROGRAMNAME = "Tidal Tails";
GLint WIDTH = 900;
GLint HEIGHT = 900;
// SDL
SDL_Window *mainWindow;
SDL_GLContext mainContext;

GLboolean init();
void check_SDL_error(int line);
void run_simulation(var, var, var, GLint);
void cleanup();

GLboolean init() {
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

    // Use GLCore
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Use OpenGL 3.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Buffer swap synchronized with monitor's vertical refresh rate
    SDL_GL_SetSwapInterval(1);
    // Init GLEW macOS
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    return true;
}

int main(int argc, char *argv[]) {
    if (!init()) return -1;
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mainWindow);
    run_simulation(1.0,0.86,12.0,1);
    cleanup();
    return 0;
}

void run_simulation(var eccentricity, var orbit_fraction, var closest_approach, GLint central_rotation) {
    //Create perturbing galaxy
    var e = eccentricity;
    var theta = 2.0*M_PI *(orbit_fraction);
    var rmin = closest_approach;

    var r = (1+e)*rmin/(1+e*cos(theta));
    var x0 = r * cos(theta);
    var y0 = r * sin (theta);
    var dvx = 1.0;
    var dvy = - ((1-e*e)*x0+e*(1+e)*rmin)/y0;
    var v0 = sqrt(2/sqrt(x0*x0+y0*y0)+(e-1)/rmin)/sqrt(dvx*dvx+dvy*dvy);

    universe universe1 = universe(true);
    universe1.generate_galaxy({x0,y0,0.0},{v0*dvx,v0*dvy,0},0.5,1.0,0.0,1,{{}},0);
    universe1.create_trail(universe1.particles.size()-1);
    universe1.generate_galaxy({0,0,0.0},{0,0,0},0.5,1.0,0.0,central_rotation,{{20*12,2},{20*18,3},{20*24,4},{20*30,5},{20*36,6},{20*42,7}},1);

    camera c = camera(WIDTH,HEIGHT);
    GLboolean loop = true;
    GLboolean paused = true;
    GLboolean logging = false;
    GLboolean reversed = false;
    GLboolean mouseAllowed = false;
    var dx,dy,zl, mousex, mousey;
    GLdouble t = 0;
    dx = 0.1;
    dy = 0.1;
    zl = 0.1;
    mousex = 0;
    mousey = 0;

    while (loop == true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) loop = false;
            if (event.type == SDL_MOUSEBUTTONDOWN and mouseAllowed) {
                switch (event.button.button){
                    case SDL_BUTTON_LEFT:
                        mousex = event.button.x;
                        mousey = event.button.y;
                        paused=true;
                        break;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP and mouseAllowed) {
                switch (event.button.button){
                    case SDL_BUTTON_LEFT:
                        //TODO: scale v
                        universe1.generate_galaxy({openGLpos(mousex,0,&c), openGLpos(mousey,1,&c),0},{15.0/c.zoom *(event.button.x-mousex)/static_cast<var>(WIDTH),-15.0/c.zoom *(event.button.y-mousey)/ static_cast<var>(HEIGHT),0.0},1.0,1.0,0.0,1,{{}},0);
                        paused=false;
                        break;
                }
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                    case SDLK_p:
                        screenshot("screenshot."+std::to_string(t)+".tga");
                        std::cout << "Screenshot created." << std::endl;
                        break;
                    case SDLK_SPACE:
                        paused = not paused;
                        std::cout << "Pause status: " << static_cast<int>(paused) << std::endl;
                        break;
                    case SDLK_r:
                        reversed= not reversed;
                        //reverse time
                        std::cout << "Time reversed." << std::endl;
                        break;
                    case SDLK_l:
                        logging = not logging;
                        //start/stop logging
                        std::cout << "Logging status: " << static_cast<int>(logging)  << std::endl;
                        break;
                    case SDLK_w:
                        update_view(&c,0.0,dy/(c.zoom),0.0);
                        break;
                    case SDLK_s:
                        update_view(&c,0.0,-1.0*dy/(c.zoom),0.0);
                        break;
                    case SDLK_a:
                        update_view(&c,-1.0*dx/(c.zoom),0.0,0.0);
                        break;
                    case SDLK_d:
                        update_view(&c,dx/(c.zoom),0.0,0.0);
                        break;
                    case SDLK_q:
                        update_view(&c,0.0,0.0,-1.0*zl);
                        break;
                    case SDLK_e:
                        update_view(&c,0.0,0.0,zl);
                        break;
                    default:
                        break;
                }
            }
        }
        if(!paused) {
            universe1.update(mainWindow,&c, reversed);
            t += getTimestep(&universe1);
        }
        if(logging){

        }
    }
}

void cleanup() {
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

void check_SDL_error(GLint line = -1) {
    std::string error = SDL_GetError();
    if (error != "") {
        std::cout << "SDL Error : " << error << std::endl;

        if (line != -1) std::cout << "\nLine : " << line << std::endl;

        SDL_ClearError();
    }
}

