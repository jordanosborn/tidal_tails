// C++ Headers
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

// OpenGL / glew / SDL Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL_opengl.h>


#include "utilities/sdl_guard.h"


// GSL Headers
//#include <gsl/gsl_errno.h>
//#include <gsl/gsl_odeiv.h>

// Headers
#include "physics/universe.h"
#include "physics/particle.h"
#include "capture/screenshot.h"
#include "capture/logger.h"
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
void run_simulation(var, var, var, GLint, GLint);
void cleanup();
void gen_perturbation(universe*, var e, var orbit_fraction, var closest_approach, GLint central_rotation, GLint pert_direction, GLint N);


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
    if(argc==5) run_simulation(atof(argv[1]),atof(argv[2]),atof(argv[3]),atoi(argv[4]),atoi(argv[5]));
    else run_simulation(1.0,0.35,2.0,1,1);

    cleanup();
    return 0;
}

void gen_perturbation(universe* u, var e, var orbit_fraction, var closest_approach, GLint central_rotation, GLint pert_direction, GLint N){
    var theta = 2.0*M_PI *(orbit_fraction);
    var rmin = closest_approach;
    var r = (1+e)*rmin/(1+e*cos(theta));
    var x0 = r * cos(theta);
    var y0 = r * sin (theta);
    var dvx = 1.0;
    var dvy = - ((1-e*e)*x0+e*(1+e)*rmin)/y0;
    var v0 = sqrt(2/sqrt(x0*x0+y0*y0)+(e-1)/rmin)/sqrt(dvx*dvx+dvy*dvy);
    u->generate_galaxy({pert_direction*x0,pert_direction*y0,0.0},{pert_direction*v0*dvx,pert_direction*v0*dvy,0},0.4,1.0,0.0,1,{{}},0);
    u->create_trail(u->particles.size()-1);
    u->generate_galaxy({0,0,0.0},{0,0,0},0.4,1.0,0.0,central_rotation,{{N*12,2},{N*18,3},{N*24,4},{N*30,5},{N*36,6},{N*42,7},{N*48,8}},1);
}

void run_simulation(var eccentricity, var orbit_fraction, var closest_approach, GLint central_rotation, GLint pert_direction) {
    //Create perturbing galaxy
    universe universe1 = universe(true);
    gen_perturbation(&universe1,eccentricity,orbit_fraction,closest_approach,central_rotation,pert_direction,40);

    logger logger1 = logger();
    camera c = camera(WIDTH,HEIGHT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    universe1.render_universe(&c);
    SDL_GL_SwapWindow(mainWindow);
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
                        screenshot("screenshot-"+std::to_string(t)+"."+std::to_string(2.0*SCALE/c.zoom)+"x"+std::to_string(2.0*SCALE/c.zoom)+".tga");
                        std::cout << "Screenshot created." << std::endl;
                        break;
                    case SDLK_SPACE:
                        paused = not paused;
                        if(t==0){
                            universe1.apply_first_step();
                            universe1.render_universe(&c);
                            t += getTimestep(&universe1);
                            if(logging) logger1.log_positions(t,universe1.particles);
                        }
                        std::cout << "Pause status: " << static_cast<int>(paused) << std::endl;
                        std::cout << 2.0*SCALE/c.zoom << "x" << 2.0*SCALE/c.zoom <<std::endl;
                        break;
                    //case SDLK_r:
                        //   reversed= not reversed;
                    //    //reverse time
                    //    std::cout << "Time reversed." << std::endl;
                    //    break;
                    case SDLK_l:
                        logging = not logging;
                        //start/stop logging
                        if(logging){
                            logger1.start("data-"+std::to_string(t)+".csv");
                            logger1.log_positions(t,universe1.particles);
                        }
                        else logger1.stop();
                        std::cout << "Logging status: " << static_cast<int>(logging)  << std::endl;
                        break;
                    case SDLK_w:
                        update_view(&c,0.0,dy/(c.zoom),0.0);
                        if(paused){
                            glClearColor(1.0, 1.0, 1.0, 1.0);
                            glClear(GL_COLOR_BUFFER_BIT);
                            universe1.render_universe(&c);
                            SDL_GL_SwapWindow(mainWindow);
                        }
                        break;
                    case SDLK_s:
                        update_view(&c,0.0,-1.0*dy/(c.zoom),0.0);
                        if(paused){
                            glClearColor(1.0, 1.0, 1.0, 1.0);
                            glClear(GL_COLOR_BUFFER_BIT);
                            universe1.render_universe(&c);
                            SDL_GL_SwapWindow(mainWindow);
                        }
                        break;
                    case SDLK_a:
                        update_view(&c,-1.0*dx/(c.zoom),0.0,0.0);
                        if(paused){
                            glClearColor(1.0, 1.0, 1.0, 1.0);
                            glClear(GL_COLOR_BUFFER_BIT);
                            universe1.render_universe(&c);
                            SDL_GL_SwapWindow(mainWindow);
                        }
                        break;
                    case SDLK_d:
                        update_view(&c,dx/(c.zoom),0.0,0.0);
                        if(paused){
                            glClearColor(1.0, 1.0, 1.0, 1.0);
                            glClear(GL_COLOR_BUFFER_BIT);
                            universe1.render_universe(&c);
                            SDL_GL_SwapWindow(mainWindow);
                        }
                        break;
                    case SDLK_q:
                        update_view(&c,0.0,0.0,-1.0*zl);
                        if(paused){
                            glClearColor(1.0, 1.0, 1.0, 1.0);
                            glClear(GL_COLOR_BUFFER_BIT);
                            universe1.render_universe(&c);
                            SDL_GL_SwapWindow(mainWindow);
                        }
                        break;
                    case SDLK_e:
                        update_view(&c,0.0,0.0,zl);
                        if(paused){
                            glClearColor(1.0, 1.0, 1.0, 1.0);
                            glClear(GL_COLOR_BUFFER_BIT);
                            universe1.render_universe(&c);
                            SDL_GL_SwapWindow(mainWindow);
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        if(!paused) {
            universe1.update(mainWindow,&c, reversed);
            t += getTimestep(&universe1);
            if(logging){
                logger1.log_positions(t,universe1.particles);
            }
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


