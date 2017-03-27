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


//TODO: color dist and particle dist and data collection
class universe{
private:
    std::vector<particle*> particles;
    std::vector<logger*> data_loggers;
    var time;
    var dt;
    var M_max;
    var M_min;
    var R_max;
    var R_min;
    //Gravitational softening parameter g prop 1/(r+epsilon)^2
    var epsilon;
    var G;
    //(density, radius)
    std::vector<std::array<GLint,2> > distribution;
    void apply_forces();

public:
    //TODO: compute g_force for each particle, update(particle), render particle , update sys time, log data,wait(in main event loop)
    void compute_forces();
    void update(SDL_Window* mainWindow,GLboolean isReversed);
    void log_data();
    void generate_galaxy(vec3 x0,vec3 v0, GLint rotation);
    void generate_universe();
    friend var getTimestep(universe*);
    //should log data at end of constructor.
    universe();
};

#endif //UNIVERSE_H
