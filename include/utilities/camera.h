//
// Created by Jordan Osborn on 18/02/2017.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "physics/universe.h"
#include "physics/particle.h"
//camera for openGL context
class universe;

class camera{
private:
    var zoom_level;

public:
    vec3 position;
    camera();
    friend void update_view(camera* c, universe* a,var dx, var dy , var zl);
};


#endif //CAMERA_H
