//
// Created by Jordan Osborn on 18/02/2017.
//

#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <vector>
#include <array>
#include <cmath>
#include "utilities/utilities.h"
#include "physics/particle.h"
#include "capture/logger.h"
#include "utilities/camera.h"
class particle;
class camera;
//TODO: color dist and particle dist and data collection
class universe{
private:
    std::vector<logger*> data_loggers;
    std::vector<GLint> galaxy_index;
    var time;
    var dt;
    var M_max;
    var M_min;
    var R_max;
    var R_min;
    //Gravitational softening parameter g prop 1/(r+epsilon)^2
    var epsilon;
    var G;
    GLboolean particles_massless;
    //(density, radius)
    void apply_forces();

public:
    //TODO: should be private
    std::vector<particle*> particles;
    //TODO: compute g_force for each particle, update(particle), render particle , update sys time, log data,wait(in main event loop)
    friend vec3 gforce(vec3 a0, particle*, particle*, var);
    void compute_forces();
    void update(SDL_Window* mainWindow, camera* c, GLboolean isReversed);
    void log_data();
    void generate_galaxy(vec3 x0,vec3 v0, var mass, var mass_min, GLint rotation, std::vector<std::array<GLint,2> > distribution);
    void render_universe(camera* c);
    friend var getTimestep(universe*);
    //should log data at end of constructor.
    universe(GLboolean);
};

#endif //UNIVERSE_H
