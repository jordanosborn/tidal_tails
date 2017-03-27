//
// Created by Jordan Osborn on 18/02/2017.
//
#include <iostream>
#include "physics/universe.h"
universe::universe(){
    G = 1.0;
    M_max = 1.0;
    M_min = 0.2;
    R_max = 0.1;
    R_min = static_cast<var>(R_max/16.0);
    epsilon = 0.001;
    time = 0.0;
    dt = 0.001;
    distribution = {{12,2},{18,3},{24,4},{30,5},{36,6}};
}

void universe::generate_galaxy(vec3 x0 = {0.0,0.0,0.0},vec3 v0 = {0.0,0.0,0.0}) {
    particles.push_back(new particle(M_max,R_max,x0,{0.0,0.0,0.0},color_white));
    var theta = 0.0;
    vec3 x = {0.0,0.0,0.0};
    vec3 v = {0.0,0.0,0.0};
    var vscale = 0.0;
    //TODO: Scale during render;
    var scale = 10.0;
    for(GLint i = 0; i<distribution.size(); i++) {
        for (GLint j = 0; j < distribution[i][0]; j++) {
            vscale = static_cast<var >(sqrt(scale * G * M_max / (distribution[i][1])));
            theta = 2.0 * M_PI * j / distribution[i][0];
            v = {static_cast<var >(-vscale * sin(theta)), static_cast<var >(vscale * cos(theta)), 0.0};
            x = {static_cast<var >(distribution[i][1] * cos(theta) / scale),
                 static_cast<var >(distribution[i][1] * sin(theta) / scale), 0.0};
            particles.push_back(new particle(M_min, R_min, add(x, x0), add(v, v0), *color_list[i]));
        }
    }
}

void universe::generate_universe(){
    generate_galaxy();
    for(GLint i = 0; i<particles.size(); i++){
        render(particles[i]);
    }
}

void universe::update(SDL_Window* mainWindow, GLboolean isReversed){
    if(isReversed) dt=-std::abs(dt);
    else dt=std::abs(dt);
    //TODO: implement updates to pos/vel integrator keeps trail
    //glClearColor(0.0,0.0,0.0,1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    apply_forces();
    //TODO: fix rendering scale and pan/zoom level
    for(GLint i = 0; i<particles.size(); i++){
        render(particles[i]);
    }
    SDL_GL_SwapWindow(mainWindow);
}

void universe::apply_forces(){
    vec3 a;
    vec3 v;
    vec3 x;
    for(int i = 0; i < particles.size(); i++){
        a={0.0,0.0,0.0};
        for(int j =0; i< particles.size(); j++){
            if(i == j) break;
            if(getMass(particles[j])<0.001) break; //TODO: float comparison
            a=add(a,mul(-G*getMass(particles[j])/std::pow((epsilon+dist(getPosition(particles[i]),getPosition(particles[j]))),2),unit(getPosition(particles[i]),getPosition(particles[j])))); //TODO: -GM/r^2 r^_accelerated i->j
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