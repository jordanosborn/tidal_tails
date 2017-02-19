//
// Created by Jordan Osborn on 18/02/2017.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <array>
#include "physics/particle.h"
#include "capture/logger.h"


//TODO: color dist and particle dist and data collection
class system{
private:
    std::vector<particle*> particles;
    std::vector<logger*> data_loggers;
    GLfloat time;
    GLfloat dt;
    GLfloat M_max;
    GLfloat R_max;
    //Gravitational softening parameter g prop 1/(r+epsilon)^2
    GLfloat epsilon;
    GLfloat G;

public:
    //if m==0 skip or only loop over large masses?
    std::array<GLfloat, 3> g_force(particle*);
    //TODO: compute g_force for each particle, update(particle), render particle , update systime, logdata,wait(in main event loop)
    void update();
    void log_data();
    void generate_galaxy();
    void generate_system();
    //should logdata at end of constructor.
    system();
};

#endif //SYSTEM_H
