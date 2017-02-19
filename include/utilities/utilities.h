//
// Created by Jordan Osborn on 13/01/2017.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include "sdl_guard.h"
#include <GL/glew.h>
#include <string>
#include <array>

std::string format_time(GLdouble);

//Hard coded for 3D for speed
std::array<GLfloat,3> add(std::array<GLfloat,3>,std::array<GLfloat,3>);
std::array<GLfloat,3> sub(std::array<GLfloat,3>,std::array<GLfloat,3>);
std::array<GLfloat,3> mul(GLfloat,std::array<GLfloat,3>);
std::array<GLfloat,3> mul(std::array<GLfloat,3>, GLfloat);
GLfloat dot(std::array<GLfloat,3>,std::array<GLfloat,3>);
std::array<GLfloat,3> cross(std::array<GLfloat,3>, std::array<GLfloat,3>);

std::string to_string(std::array<GLfloat,3>);
std::string to_string(std::array<GLfloat,4>);

#endif //UTILITIES_H
