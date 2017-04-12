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

class universe{
private:
    std::vector<GLint> galaxy_index;
    std::vector<GLint> trails_kept;
    std::vector<std::vector<vec3> > particle_trails;
    var time;
    var dt;
    var M_max;
    var M_min;
    var R_max;
    var R_min;

    var prev_time;
    //var epsilon;
    var G;
    GLboolean particles_massless;
    //(density, radius)
    void apply_forces();

public:
    //TODO: should be private
    std::vector<particle*> particles;
    void apply_first_step();
    void apply_first_step_single_particle();
    friend vec3 gforce(vec3 a0, particle*, particle*, var);
    void compute_forces();
    void create_trail(GLint particle_num);
    void update(SDL_Window* mainWindow, camera* c, GLboolean isReversed);
    void generate_galaxy(vec3 x0,vec3 v0, var R, var mass, var mass_min, GLint rotation, std::vector<std::array<GLint,2> > distribution, GLboolean fixed);
    void render_universe(camera* c);
    friend var getTimestep(universe*);
    //should log data at end of constructor.
    universe(GLboolean);
};

#endif //UNIVERSE_H
