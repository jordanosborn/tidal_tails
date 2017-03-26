//
// Created by Jordan Osborn on 18/02/2017.
//

#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <vector>
#include <array>
#include "utilities/utilities.h"
#include "physics/particle.h"
#include "capture/logger.h"


//TODO: color dist and particle dist and data collection
class universe{
private:
    std::vector<particle*> particles;
    std::vector<logger*> data_loggers;
    GLfloat time;
    GLfloat dt;
    GLfloat M_max;
    GLfloat M_min;
    GLfloat R_max;
    GLfloat R_min;
    //Gravitational softening parameter g prop 1/(r+epsilon)^2
    GLfloat epsilon;
    GLfloat G;
    //(density, radius)
    std::vector<std::array<GLint,2> > distribution;
    void apply_forces();

public:
    //if m==0 skip or only loop over large masses?
    std::array<GLfloat, 3> g_force(particle*);
    //TODO: compute g_force for each particle, update(particle), render particle , update sys time, log data,wait(in main event loop)
    void compute_forces();
    void update();
    void log_data();
    void generate_galaxy(std::array<GLfloat,3> x0,std::array<GLfloat,3> v0);
    void generate_universe();
    //should log data at end of constructor.
    universe();
};

#endif //UNIVERSE_H
