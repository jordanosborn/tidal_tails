//
// Created by Jordan Osborn on 01/04/2017.
//
#include "utilities/camera.h"

camera::camera(){
    position = {0.0,0.0,0.0};
    zoom_level = 0.0;
    zoom = 1.0;
}

void update_view(camera* c,var dx, var dy, var zl) {
    c->position = {c->position[0]+dx,c->position[1]+dy,0.0};
    c->zoom_level += zl;
    c->zoom = std::exp(c->zoom_level);
}

