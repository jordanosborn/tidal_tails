//
// Created by jo357 on 19/01/17.
//

#include "physics/particle.h"

const GLfloat& getMass(particle* a){
    return a->mass;
}
const GLfloat& getRadius(particle* a){
    return a->radius;
}
const std::array<GLfloat,3>& getPosition(particle* a){
    return a->position;
}
const std::array<GLfloat,3>& getVelocity(particle* a){
    return a->velocity;
}
const std::array<GLfloat,3>& getAcceleration(particle* a){
    return a->acceleration;
}

const std::array<GLfloat,4>& getColor(particle* a){
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

void update(particle* p,std::array<GLfloat,3> x,std::array<GLfloat,3> v, std::array<GLfloat,3> a){
    p->acceleration = a;
    p->velocity = v;
    p->position = x;
}
void render(particle* a){
    GLint subdivisions = 20;
    GLUquadricObj *quadric=gluNewQuadric();
    GLfloat color[4] = {getColor(a)[0],getColor(a)[1],getColor(a)[2],getColor(a)[3]};
    glColor4fv(color);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glPushMatrix();
    glTranslatef( getPosition(a)[0],getPosition(a)[1],getPosition(a)[2]);
    gluSphere(quadric, getRadius(a), subdivisions,subdivisions);
    //glRotatef(theta,0.0,1.0,0.0);
    glPopMatrix();
    gluDeleteQuadric(quadric);
}
