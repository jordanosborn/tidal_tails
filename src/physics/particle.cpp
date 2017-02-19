//
// Created by jo357 on 19/01/17.
//

#include "physics/particle.h"

GLfloat getMass(particle* a){
    return a->mass;
}
GLfloat getRadius(particle* a){
    return a->radius;
}
std::array<GLfloat,3> getPosition(particle* a){
    return a->position;
}
std::array<GLfloat,3> getVelocity(particle* a){
    return a->velocity;
}
std::array<GLfloat,3> getAcceleration(particle* a){
    return a->acceleration;
}

std::array<GLfloat,4> getColor(particle* a){
    return a->color;
}

particle::particle(GLfloat m, GLfloat r, std::array<GLfloat,3> x0, std::array<GLfloat,3> v0, std::array<GLfloat,4> C) {
    mass = m;
    radius = r;
    position = x0;
    velocity = v0;
    acceleration = {0.0,0.0,0.0};
    color = C;
}

void update(particle* p,std::array<GLfloat,3> a){

}
void render(particle* p){

}
