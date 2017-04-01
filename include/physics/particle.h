//
// Created by jo357 on 19/01/17.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include "utilities/sdl_guard.h"
#include "utilities/utilities.h"
#include "utilities/camera.h"
#include <GL/glew.h>
#include <array>

class camera;

class particle {
private:
    var radius;
    var mass;
    vec4 color;
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
public:
    friend const var& getRadius(particle*);
    friend const var& getMass(particle*);
    friend const vec3& getPosition(particle*);
    friend const vec3& getVelocity(particle*);
    friend const vec3& getAcceleration(particle*);
    friend const vec4& getColor(particle*);
    friend void update_particle(particle* p,vec3 x,vec3 v, vec3 a);
    friend void update_particle_internal(particle* p, var R, var M);
    friend void render(camera*, particle*);
    particle(var m, var r, vec3 x0, vec3 v0, vec4 C);
};


#endif //PARTICLE_H
