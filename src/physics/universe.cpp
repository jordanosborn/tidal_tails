//
// Created by Jordan Osborn on 18/02/2017.
//

#include "physics/universe.h"
universe::universe(){
    G = 1.0;
    M_max = 1.0;
    M_min = 0.0;
    R_max = 0.1;
    R_min = static_cast<GLfloat >(R_max/16.0);
    epsilon = 0.0001;
    time = 0.0;
    dt = 0.001;
    distribution = {{12,2},{18,3},{24,4},{30,5},{36,6}};
}

void universe::generate_galaxy(std::array<GLfloat,3> x0 = {0.0,0.0,0.0},std::array<GLfloat,3> v0 = {0.0,0.0,0.0}) {
    particles.push_back(new particle(M_max,R_max,x0,{0.0,0.0,0.0},color_white));
    GLfloat theta = 0.0;
    std::array<GLfloat ,3> x = {0.0,0.0,0.0};
    std::array<GLfloat ,3> v = {0.0,0.0,0.0};
    GLfloat vscale = 0.0;
    //TODO: Scale during render;
    GLfloat scale = 10.0;
    for(GLint i = 0; i<distribution.size(); i++) {
        for (GLint j = 0; j < distribution[i][0]; j++) {
            vscale = static_cast<GLfloat >(sqrt(G*M_max/distribution[i][1]));
            theta = 2.0 * M_PI * j / distribution[i][0];
            v = {static_cast<GLfloat >(vscale*sin(theta)), static_cast<GLfloat >(vscale*cos(theta) ), 0.0};
            x = {static_cast<GLfloat >(distribution[i][1] * cos(theta) / scale), static_cast<GLfloat >(distribution[i][1] * sin(theta) / scale), 0.0};
            particles.push_back(new particle(M_min, R_min, add(x, x0), add(v,v0), *color_list[i]));
        }
    }
}

void universe::generate_universe(){
    generate_galaxy();
}

void universe::update(){
    //TODO: implement updates to pos/vel integrator
    for(GLint i = 0; i<particles.size(); i++){
        render(particles[i]);
    }
}

void universe::apply_forces(){
    std::array<GLfloat ,3> a;
    for(int i = 0; i < particles.size(); i++){
        a={0.0,0.0,0.0};
        for(int j =0; i< particles.size(); j++){
            if(i == j) break;
            if(getMass(particles[j])==0.0) break; //TODO: float comparison
            a=add(a,mul(G*getMass(particles[j])/dist(particles[i],particles[j]),unit(particles[i],particles[j])); //TODO: -GM/r^2 r^_accelerated i->j
        }
        
    }
}
