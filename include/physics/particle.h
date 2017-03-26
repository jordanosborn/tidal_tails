//
// Created by jo357 on 19/01/17.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include "sdl_guard.h"
#include "utilities/utilities.h"
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
    friend const GLfloat& getRadius(particle*);
    friend const GLfloat& getMass(particle*);
    friend const std::array<GLfloat,3>& getPosition(particle*);
    friend const std::array<GLfloat,3>& getVelocity(particle*);
    friend const std::array<GLfloat,3>& getAcceleration(particle*);
    friend const std::array<GLfloat,4>& getColor(particle*);
    friend void update(particle* p,std::array<GLfloat,3> x,std::array<GLfloat,3> v, std::array<GLfloat,3> a);
    friend void render(particle*);
    particle(GLfloat m, GLfloat r, std::array<GLfloat,3> x0, std::array<GLfloat,3> v0, std::array<GLfloat,4> C);
};


#endif //PARTICLE_H
