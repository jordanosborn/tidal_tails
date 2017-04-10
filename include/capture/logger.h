#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>
#include <vector>
#include "utilities/utilities.h"
#include "physics/particle.h"

class particle;
//logs data that can be later plotted with gnuplot
class logger{
private:
    std::fstream f;
    std::string title;
public:
    void log_positions(var t, std::vector<particle*> particles);
    logger();
    void stop();
    void start(std::string);

};

#endif //LOGGER_H
