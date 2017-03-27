//
// Created by jo357 on 19/01/17.
//

#include "physics/particle.h"

const var& getMass(particle* a){
    return a->mass;
}
const var& getRadius(particle* a){
    return a->radius;
}
const vec3& getPosition(particle* a){
    return a->position;
}
const vec3& getVelocity(particle* a){
    return a->velocity;
}
const vec3& getAcceleration(particle* a){
    return a->acceleration;
}

const vec4& getColor(particle* a){
    return a->color;
}

particle::particle(var m, var r, vec3 x0, vec3 v0, vec4 C) {
    mass = m;
    radius = r;
    position = x0;
    velocity = v0;
    acceleration = {0.0,0.0,0.0};
    color = C;
}

void update_particle(particle* p,vec3 x,vec3 v, vec3 a){
    p->acceleration = a;
    p->velocity = v;
    p->position = x;
}
void render(particle* a){
    GLint subdivisions = 20;
    GLUquadricObj *quadric=gluNewQuadric();
//TODO: could be slowdown
    var color[4] = {getColor(a)[0],getColor(a)[1],getColor(a)[2],getColor(a)[3]};
    glColor4dv(color);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glPushMatrix();
    glTranslatef( getPosition(a)[0],getPosition(a)[1],getPosition(a)[2]);
    gluSphere(quadric, getRadius(a), subdivisions,subdivisions);
    //glRotatef(theta,0.0,1.0,0.0);
    glPopMatrix();
    gluDeleteQuadric(quadric);
}
