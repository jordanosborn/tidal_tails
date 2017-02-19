//
// Created by Jordan Osborn on 13/01/2017.
#include "utilities/utilities.h"

std::string format_time(GLdouble t){
    GLint h = floor(t/3600);
    GLint m = floor(t/60-h*60);
    GLint s = round(t-m*60-h*3600);
    return std::to_string(h)+"."+std::to_string(m)+"."+std::to_string(s);
}

std::array<GLfloat,3> add(std::array<GLfloat,3> a,std::array<GLfloat,3> b){
    return std::array<GLfloat,3>{{a[0]+b[0],a[1]+b[1],a[2]+b[2]}};
}
std::array<GLfloat,3> sub(std::array<GLfloat,3> a,std::array<GLfloat,3> b){
    return std::array<GLfloat,3>{{a[0]-b[0],a[1]-b[1],a[2]-b[2]}};
}
std::array<GLfloat,3> mul(GLfloat a,std::array<GLfloat,3> b){
    return std::array<GLfloat,3>{{a*b[0],a*b[1],a*b[2]}};
}
std::array<GLfloat,3> mul(std::array<GLfloat,3> a, GLfloat b){
    return std::array<GLfloat,3>{{b*a[0],b*a[1],b*a[2]}};
};
GLfloat dot(std::array<GLfloat,3> a,std::array<GLfloat,3> b){
    return (a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);
}
std::array<GLfloat,3> cross(std::array<GLfloat,3> a, std::array<GLfloat,3> b){
    return std::array<GLfloat,3>{{a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]}};
};

std::string to_string(std::array<GLfloat,3>a){
        return "[" + std::to_string(a[0]) + "," + std::to_string(a[1]) + "," + std::to_string(a[2])+"]";
}

std::string to_string(std::array<GLfloat,4>a){
    return "[" + std::to_string(a[0]) + "," + std::to_string(a[1]) + "," + std::to_string(a[2]) +  "," + std::to_string(a[3]) + "]";
}

//

