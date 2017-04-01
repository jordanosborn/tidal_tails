//
// Created by Jordan Osborn on 01/04/2017.
//
#include "utilities/camera.h"

camera::camera(){
    position = {0.0,0.0,0.0};
    zoom_level = 1.0;
}

void update_view(camera* c,universe* a,var dx, var dy, var zl) {
    c->position=add(c->position,{dx,dy,0.0});
    c->zoom_level += zl;
    if(c->zoom_level<0.1) c->zoom_level=0.1;

}

