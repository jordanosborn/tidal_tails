//
// Created by Jordan Osborn on 13/01/2017.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include "sdl_guard.h"
#include <GL/glew.h>
#include <string>
#include <array>

//TODO: change types from var to var
typedef GLdouble var;
//TODO: convert to vec3
typedef std::array<var, 3> vec3;
typedef std::array<var, 4> vec4;
std::string format_time(GLdouble);

//Hard coded for 3D for speed
vec3 add(vec3,vec3);
vec3 sub(vec3,vec3);
vec3 mul(var,vec3);
vec3 mul(vec3, var);
var dot(vec3,vec3);
var abs(std::array<var, 3>);

//TODO: check for speed
var dist(vec3,vec3);
vec3 unit(vec3,vec3);
vec3 cross(vec3, vec3);

std::string to_string(vec3);
std::string to_string(vec4);

//colors
extern vec4 color_red;
extern vec4 color_yellow;
extern vec4 color_green;
extern vec4 color_cyan;
extern vec4 color_blue;
extern vec4 color_magenta;
extern vec4 color_black;
extern vec4 color_white;

extern std::array<vec4*,6> color_list;

#endif //UTILITIES_H
