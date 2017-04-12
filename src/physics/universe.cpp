#include <iostream>
#include "physics/universe.h"
universe::universe(GLboolean massless_particles){
    G = 1.0;
    M_max = 1.0;
    M_min = 0.00;
    R_max = 0.05;
    R_min = static_cast<var>(R_max/16.0);
    particles_massless = massless_particles;
    time = 0.0;

    dt = 0.005;
    //epsilon = 0.01;
    galaxy_index.push_back(0);
    prev_time = 0.0;

}

void universe::render_universe(camera* c){
    //renders all large central masses
    for(GLint i = 0; i<galaxy_index.size()-1; i++){
        render(c,particles[galaxy_index[i]]);
    }
    //renders test masses
    GLboolean notLargeMass;
    for(GLint i = 0; i<particles.size();i++){
        notLargeMass=1;
        for(GLint j = 0; j<galaxy_index.size()-1; j++){
            if(i==galaxy_index[j]) notLargeMass=0;
        }
        if(notLargeMass) render(c,particles[i]);
    }
    //renders any trails
    for(int i=0;i<trails_kept.size();i++){
        for(int j=1;j<particle_trails[i].size(); j++){
            glLineWidth(1.5);
            glColor4f(0.0, 0.0, 1.0,1.0);
            glBegin(GL_LINES);
            glVertex3f(c->zoom/SCALE * (particle_trails[i][j-1][0]-c->position[0]),c->zoom/SCALE * (particle_trails[i][j-1][1]-c->position[1]), c->zoom/SCALE * (particle_trails[i][j-1][2]-c->position[2]));
            glVertex3f(c->zoom/SCALE * (particle_trails[i][j][0]-c->position[0]),c->zoom/SCALE * (particle_trails[i][j][1]-c->position[1]), c->zoom/SCALE * (particle_trails[i][j][2]-c->position[2]));
            glEnd();
        }
    }
    //renders grid lines
    render_grid(c);
}

void universe::generate_galaxy(vec3 x0 = {0.0,0.0,0.0},vec3 v0 = {0.0,0.0,0.0},var R = 5.0, var mass = 1.0, var mass_min = 0.0, GLint rotation = 1, std::vector<std::array<GLint,2> > distribution ={{}} ,GLboolean fixed = 0) {
    particles.push_back(new particle(mass,R,x0,v0,color_green,fixed));
    var theta = 0.0;
    vec3 x = {0.0,0.0,0.0};
    vec3 v = {0.0,0.0,0.0};
    var r_min = R/SCALE;
    var vscale = 0.0;
    for(GLint i = 0; i<distribution.size(); i++) {
        for (GLint j = 0; j < distribution[i][0]; j++) {
            vscale = static_cast<var >(sqrt(G * mass / (distribution[i][1])));
            theta = 2.0 * M_PI * j / distribution[i][0];
            v = {static_cast<var >(-rotation*vscale * sin(theta)), static_cast<var >(rotation*vscale * cos(theta)), 0.0};
            x = {static_cast<var >(distribution[i][1] * cos(theta)),
                 static_cast<var >(distribution[i][1] * sin(theta)), 0.0};
            particles.push_back(new particle(mass_min, r_min, add(x, x0), add(v, v0), color_red,0));
        }
    }
    galaxy_index.push_back(particles.size());
}

void universe::create_trail(GLint particle_num){
    if(!particles[particle_num]->isFixed) {
        trails_kept.push_back(particle_num);
        particle_trails.push_back({getPosition(particles[particle_num])});
    }
}


void universe::update(SDL_Window* mainWindow, camera* c, GLboolean isReversed) {
    if (isReversed) dt = -std::abs(dt);
    else dt = std::abs(dt);
    apply_forces();
    var current_time = SDL_GetTicks();
    //adaptive fps to render. 1000*100/N = FPS.
    //lim to 30
    var time_step = particles.size()/100.0;
    if(1000.0/time_step>30.0) time_step = 1000.0/30.0;

    if (current_time - prev_time > time_step){
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        render_universe(c);
        SDL_GL_SwapWindow(mainWindow);
        prev_time=current_time;
        for(int i=0;i<trails_kept.size();i++){
            particle_trails[i].push_back(getPosition(particles[i]));
        }
    }

    time+=dt;
}

vec3 gforce(vec3 a0,particle* p, particle* b, var G = 1.0){
    vec3 a;
    var R;
    R = dist(getPosition(p), getPosition(b));
    if (R > getRadius(b))
        a = add(a0, mul(-G * getMass(b) / std::pow((R), 2), unit(getPosition(p), getPosition(b)))); //TODO: -GM/r^2 r^_accelerated i->j
    else//TODO: changed to repulsive force
        a = add(a0, mul((-1.0)*-G * getMass(b) / (R*R) / std::pow(getRadius(b), 3),unit(getPosition(p), getPosition(b))));
    return a;
}

void universe::apply_first_step(){
    vec3 a;
    vec3 v;
    vec3 x;

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
        v = add(getVelocity(particles[i]),mul(0.5*dt,add(a,getAcceleration(particles[i]))));
        x = add(add(getPosition(particles[i]),mul(dt,getVelocity(particles[i]))),mul(0.5*dt*dt,getAcceleration(particles[i])));
        update_particle(particles[i],x,v,a);
    }
    time+=dt;
}
void universe::apply_first_step_single_particle(){
    vec3 a;
    vec3 v;
    vec3 x;

    GLint i = particles.size()-1;
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
    v = add(getVelocity(particles[i]),mul(0.5*dt,add(a,getAcceleration(particles[i]))));
    x = add(add(getPosition(particles[i]),mul(dt,getVelocity(particles[i]))),mul(0.5*dt*dt,getAcceleration(particles[i])));
    update_particle(particles[i],x,v,a);
}


void universe::apply_forces(){
    vec3 a;
    vec3 v;
    vec3 x;

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
        //leapfrog
        //v=add(getVelocity(particles[i]),mul(dt,a));
        //x=add(getPosition(particles[i]),mul(dt,v));

        //verlet O(dt^4)
        x = add(add(mul(2.0,getPosition(particles[i])),mul(-1.0,getPositionOld(particles[i]))),mul(dt*dt,a));
        //is one time step behind O(dt^2)
        v =  mul(1.0/(2.0*dt),add(x,mul(-1.0,getPositionOld(particles[i]))));
        update_particle(particles[i],x,v,a);
    }
}

var getTimestep(universe* a){
    return a->dt;
}


