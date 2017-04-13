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

const vec3& getPositionOld(particle* a){
    return a->position_old;
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

particle::particle(var m, var r, vec3 x0, vec3 v0, vec4 C, GLboolean fixed) {
    mass = m;
    radius = r;
    position = x0;
    velocity = v0;
    acceleration = {0.0,0.0,0.0};
    color = C;
    isFixed = fixed;
}

void update_particle(particle* p,vec3 x,vec3 v, vec3 a){
    if(!p->isFixed){
        p->acceleration = a;
        p->velocity = v;
        p->position_old = p->position;
        p->position = x;
    }
}

void update_particle_internal(particle* p, var R, var M){
    p->mass = M;
    p->radius = R;
}

void render(camera*  c, particle* a){
    GLint subdivisions = 20;
    GLUquadricObj *quadric = gluNewQuadric();
    var color[4] = {getColor(a)[0],getColor(a)[1],getColor(a)[2],getColor(a)[3]};
    glColor4dv(color);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glPushMatrix();
    glTranslatef(c->zoom*(getPosition(a)[0]-c->position[0])/SCALE,
                 c->zoom*(getPosition(a)[1]-c->position[1])/SCALE,
                 c->zoom*(getPosition(a)[2]-c->position[2])/SCALE);
    gluSphere(quadric, c->zoom*getRadius(a)/SCALE, subdivisions,subdivisions);
    //glRotatef(0.01,0.0,0.0,1.0);
    glPopMatrix();
    gluDeleteQuadric(quadric);
}
