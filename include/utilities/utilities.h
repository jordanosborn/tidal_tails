//
// Created by Jordan Osborn on 13/01/2017.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include "sdl_guard.h"
#include <GL/glew.h>
#include <string>
#include <array>

//TODO: change types from GLfloat to var
typedef GLdouble var;
//TODO: convert to vec3
typedef std::array<GLfloat, 3> vec3;
typedef std::array<GLfloat, 3> vec4;
std::string format_time(GLdouble);

//Hard coded for 3D for speed
std::array<GLfloat,3> add(std::array<GLfloat,3>,std::array<GLfloat,3>);
std::array<GLfloat,3> sub(std::array<GLfloat,3>,std::array<GLfloat,3>);
std::array<GLfloat,3> mul(GLfloat,std::array<GLfloat,3>);
std::array<GLfloat,3> mul(std::array<GLfloat,3>, GLfloat);
GLfloat dot(std::array<GLfloat,3>,std::array<GLfloat,3>);
GLfloat abs(std::array<GLfloat, 3>);

//TODO: check for speed
GLfloat dist(std::array<GLfloat,3>,std::array<GLfloat,3>);
std::array<GLfloat ,3> unit(std::array<GLfloat,3>,std::array<GLfloat,3>);
std::array<GLfloat,3> cross(std::array<GLfloat,3>, std::array<GLfloat,3>);

std::string to_string(std::array<GLfloat,3>);
std::string to_string(std::array<GLfloat,4>);

//colors
extern std::array<GLfloat,4> color_red;
extern std::array<GLfloat,4> color_yellow;
extern std::array<GLfloat,4> color_green;
extern std::array<GLfloat,4> color_cyan;
extern std::array<GLfloat,4> color_blue;
extern std::array<GLfloat,4> color_magenta;
extern std::array<GLfloat,4> color_black;
extern std::array<GLfloat,4> color_white;

extern std::array<std::array<GLfloat ,4>*,6> color_list;

#endif //UTILITIES_H
