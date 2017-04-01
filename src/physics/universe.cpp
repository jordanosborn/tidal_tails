//
// Created by Jordan Osborn on 18/02/2017.
//
#include <iostream>
#include "physics/universe.h"
universe::universe(GLboolean massless_particles){
    G = 1.0;
    M_max = 1.0;
    M_min = 0.00;
    R_max = 0.05;
    R_min = static_cast<var>(R_max/16.0);
    particles_massless = massless_particles;
    epsilon = 0.001;
    time = 0.0;
    dt = 0.001;
    galaxy_index.push_back(0);

}

void universe::render_universe(camera* c){
    for(GLint i = 0; i<galaxy_index.size()-1; i++){
        render(c,particles[galaxy_index[i]]);
    }
    GLboolean notLargeMass;
    for(GLint i = 0; i<particles.size();i++){
        notLargeMass=1;
        for(GLint j = 0; j<galaxy_index.size()-1; j++){
            if(i==galaxy_index[j]) notLargeMass=0;
        }
        if(notLargeMass) render(c,particles[i]);
    }
}

void universe::generate_galaxy(vec3 x0 = {0.0,0.0,0.0},vec3 v0 = {0.0,0.0,0.0}, var mass = 1.0, var mass_min = 0.0, GLint rotation = 1, std::vector<std::array<GLint,2> > distribution ={{}} ) {
    particles.push_back(new particle(mass,R_max,x0,v0,color_white));
    var theta = 0.0;
    vec3 x = {0.0,0.0,0.0};
    vec3 v = {0.0,0.0,0.0};
    var vscale = 0.0;
    //TODO: Scale during render;
    var scale = 10.0;
    for(GLint i = 0; i<distribution.size(); i++) {
        for (GLint j = 0; j < distribution[i][0]; j++) {
            vscale = static_cast<var >(sqrt(scale * G * mass / (distribution[i][1])));
            theta = 2.0 * M_PI * j / distribution[i][0];
            v = {static_cast<var >(-rotation*vscale * sin(theta)), static_cast<var >(rotation*vscale * cos(theta)), 0.0};
            x = {static_cast<var >(distribution[i][1] * cos(theta) / scale),
                 static_cast<var >(distribution[i][1] * sin(theta) / scale), 0.0};
            particles.push_back(new particle(mass_min, R_min, add(x, x0), add(v, v0), *color_list[galaxy_index.size()-1]));
        }
    }
    galaxy_index.push_back(particles.size());
}



void universe::update(SDL_Window* mainWindow, camera* c, GLboolean isReversed){
    if(isReversed) dt=-std::abs(dt);
    else dt=std::abs(dt);
    //TODO: implement updates to pos/vel integrator keeps trail
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    apply_forces();
    //TODO: fix rendering scale and pan/zoom level
    render_universe(c);
    SDL_GL_SwapWindow(mainWindow);
}

vec3 gforce(vec3 a0,particle* p, particle* b, var G = 1.0){
    vec3 a;
    var R;
    R = dist(getPosition(p), getPosition(b));
    if (R > getRadius(b))
        a = add(a0, mul(-G * getMass(b) / std::pow((R), 2), unit(getPosition(p), getPosition(b)))); //TODO: -GM/r^2 r^_accelerated i->j
    else
        a = add(a0, mul(-G * getMass(b) * R / std::pow(getRadius(b), 3),
                       unit(getPosition(p), getPosition(b))));
    return a;
}

void universe::apply_forces(){
    vec3 a;
    vec3 v;
    vec3 x;
    var R;
    //TODO: make more efficient
    for(GLint i = 0; i < particles.size(); i++){
        a={0.0,0.0,0.0};
        if(particles_massless){
            for(GLint j = 0; j<galaxy_index.size()-1;j++){
                if(i==galaxy_index[j]) continue;
                else{
                    a = gforce(a, particles[i],particles[galaxy_index[j]],G);
                }
            }
        }
        else {
            for (GLint j = 0; j < particles.size(); j++) {
                if (i == j or getMass(particles[j]) < 0.000001) continue;
                else {
                    a = gforce(a,particles[i],particles[j],G);
                }
            }
        }
    //TODO: change to RK4
        v=add(getVelocity(particles[i]),mul(dt,a));
        x=add(getPosition(particles[i]),mul(dt,v));

        //v = add(getVelocity(particles[i]),mul(0.5*dt,add(a,getAcceleration(particles[i]))));
        //x = add(add(getPosition(particles[i]),mul(dt,getVelocity(particles[i]))),mul(0.5*dt*dt,getAcceleration(particles[i])));
        update_particle(particles[i],x,v,a);
    }
}

var getTimestep(universe* a){
    return a->dt;
}

void universe::log_data() {

}

