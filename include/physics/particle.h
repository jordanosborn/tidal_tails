//
// Created by jo357 on 19/01/17.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include "sdl_guard.h"
#include <GL/glew.h>
#include <array>

class particle {
private:
    GLfloat radius;
    GLfloat mass;
    std::array<GLfloat,4> color;
    std::array<GLfloat,3> position;
    std::array<GLfloat,3> velocity;
    std::array<GLfloat,3> acceleration;
public:
    inline friend GLfloat getRadius(particle*);
    inline friend GLfloat getMass(particle*);
    inline friend std::array<GLfloat,3> getPosition(particle*);
    inline friend std::array<GLfloat,3> getVelocity(particle*);
    inline friend std::array<GLfloat,3> getAcceleration(particle*);
    inline friend std::array<GLfloat,4> getColor(particle*);
    friend void update(particle*,std::array<GLfloat,3>);
    friend void render(particle*);
    particle(GLfloat, GLfloat, std::array<GLfloat,3>, std::array<GLfloat,3>, std::array<GLfloat,4>);
};


#endif //PARTICLE_H
