// Headerphile.com OpenGL Tutorial part 1
// A Hello World in the world of OpenGL ( creating a simple windonw and setting background color )
// Source code is an C++ adaption / simplicication of : https://www.opengl.org/wiki/Tutorial1:_Creating_a_Cross_Platform_OpenGL_3.2_Context_in_SDL_(C_/_SDL)
// Compile : clang++ main.cpp -lGL -lSDL2 -std=c++11 -o Test

// C++ Headers
#include <string>
#include <iostream>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>


// SDL2 Headers
#include "sdl_guard.h"
#include "capture/screenshot.h"
#include "utilities/utilities.h"

std::string PROGRAMNAME = "Computer Project";
GLint WIDTH=800;
GLint HEIGHT = 800;
GLint N = 3;
GLfloat R = 0.2;
GLfloat THETA = 3.141926/4.0;
GLfloat color[4]= {1,1,0,1};
GLfloat X[3]={0,0,0};
GLdouble system_time = 0;


// Our SDL_Window ( just like with SDL2 wihout OpenGL)
SDL_Window *mainWindow;

// Our opengl context handle
SDL_GLContext mainContext;

bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);
void RunGame();
void Cleanup();
//should be in particle source file as render function
void renderSphere(GLfloat, GLfloat, GLfloat, GLfloat,GLfloat* GLint, GLfloat);


void renderSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat* color_param, GLint subdivisions,GLfloat theta=0)
{
    //the same quadric can be re-used for drawing many spheres
    GLUquadricObj *quadric=gluNewQuadric();
    glColor4fv(color_param);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glPushMatrix();
    glTranslatef( x,y,z );

    gluSphere(quadric, radius, subdivisions,subdivisions);
    glRotatef(theta,0.0,1.0,0.0);
    glPopMatrix();
    gluDeleteQuadric(quadric);
}

bool Init()
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL\n";
        return false;
    }

    mainWindow = SDL_CreateWindow(PROGRAMNAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    // Check that everything worked out okay
    if (!mainWindow)
    {
        std::cout << "Unable to create window\n";
        CheckSDLError(__LINE__);
        return false;
    }

    // Create our opengl context and attach it to our window
    mainContext = SDL_GL_CreateContext(mainWindow);

    SetOpenGLAttributes();

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    // Init GLEW
    // Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    return true;
}

bool SetOpenGLAttributes()
{
    // Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.2 is part of the modern versions of OpenGL, but most video cards should be able to run it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return true;
}

int main(int argc, char *argv[])
{
    if (!Init())
        return -1;

    // Clear our buffer with a black background
    // This is the same as :
    // 		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
    // 		SDL_RenderClear(&renderer);
    //
    glClearColor(0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mainWindow);
    RunGame();

    Cleanup();

    return 0;
}

GLboolean rUP=true;
GLboolean rDOWN=false;
void RunGame()
{
    bool loop = true;
    while (loop)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                loop = false;

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                    case SDLK_q:
                        // Cover with red and update
                        R=0.2;
                        N=3;
                        X[0]=0,X[1]=0,X[2]=0;
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;
                        break;
                    case SDLK_w:
                        // Cover with red and update
                        X[1]+=0.05;
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;
                        break;
                    case SDLK_a:
                        // Cover with red and update
                        X[0]-=0.05;
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;
                        break;
                    case SDLK_s:
                        // Cover with red and update
                        X[1]-=0.05;
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;
                        break;
                    case SDLK_d:
                        // Cover with red and update
                        X[0]+=0.05;
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;
                        break;
                    case SDLK_UP:
                        N++;
                        // Cover with blue and update
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;

                        break;
                    case SDLK_DOWN:
                        N--;
                        // Cover with blue and update
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;
                        break;
                    case SDLK_LEFT:
                        R/=2;
                        // Cover with blue and update
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;

                        break;
                    case SDLK_RIGHT:
                        R*=2;
                        // Cover with blue and update
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        renderSphere(X[0],X[1],X[2],R,color,N);
                        SDL_GL_SwapWindow(mainWindow);
                        system_time+=6.1;
                        break;
                    case SDLK_p:
                        screenshot("screenshot."+ format_time(system_time)+".tga");
                        break;
                    default:
                        break;
                }
            }
            else if(event.type == SDL_KEYUP)
            {

            }
        }

        // Swap our back buffer to the front
        // This is the same as :
        // 		SDL_RenderPresent(&renderer);
    }
}

void Cleanup()
{
    // Delete our OpengL context
    SDL_GL_DeleteContext(mainContext);

    // Destroy our window
    SDL_DestroyWindow(mainWindow);

    // Shutdown SDL 2
    SDL_Quit();
}

void CheckSDLError(GLint line = -1)
{
    std::string error = SDL_GetError();

    if (error != "")
    {
        std::cout << "SLD Error : " << error << std::endl;

        if (line != -1)
            std::cout << "\nLine : " << line << std::endl;

        SDL_ClearError();
    }
}

void PrintSDL_GL_Attributes()
{
    GLint value = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}
