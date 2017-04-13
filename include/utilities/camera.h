#ifndef CAMERA_H
#define CAMERA_H
#include "physics/universe.h"
#include "physics/particle.h"
//camera for openGL context

class camera{
private:
    var zoom_level;

public:
    vec3 position;
    var zoom;
    GLint width,height;
    camera(GLint,GLint);
    friend void update_view(camera* c,var dx, var dy , var zl);
};


#endif //CAMERA_H
