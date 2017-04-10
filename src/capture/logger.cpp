//
// Created by Jordan Osborn on 27/03/2017.
//
#include "capture/logger.h"
#include <iostream>
logger::logger(){

}

void logger::start(std::string s){
    f.open(s,std::fstream::out | std::fstream::trunc);
    title = s;
    std::cout << title << " opened.\n";
}

void logger::stop(){
    f.close();
    std::cout << title << " closed.\n";
}

void logger::log_positions(var t, std::vector<particle *> particles) {
    f << t;
    for(int i = 0; i<particles.size(); i++){
        f << "," << to_string(getPosition(particles[i]));
    }
    f << '\n';
    std::cout << title << " logged.\n";
}


