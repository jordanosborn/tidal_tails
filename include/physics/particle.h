//
// Created by jo357 on 19/01/17.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include "sdl_guard.h"
#include <GL/glew.h>
#include <vector>
//implementation details??
class particle {
private:
    GLint radius;
    GLfloat inverse_mass;
    GLfloat color[4];
    std::vector<GLfloat> position;
    std::vector<GLfloat> velocity;
    std::vector<GLfloat> acceleration;
public:
    friend void setRadius(GLfloat);
    friend GLfloat getRadius(GLint);
    friend void setMass(GLfloat);
    friend GLfloat getInverseMass(GLint);
    friend std::vector<GLfloat> getPosition(GLint);
    friend void setPosition();
    particle();
    ~particle();

};


#endif //PARTICLE_H
