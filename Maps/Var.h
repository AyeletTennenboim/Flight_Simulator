#ifndef FLIGHT_SIMULATOR_VAR_H
#define FLIGHT_SIMULATOR_VAR_H

#include <string>
#include "CommandsMap.h"
#include "../Commands/ConnectCommand.h"

using namespace std;

/**
 * Var Class
 *
 * This class represents a variable that has the following members:
 * numeric value, name of the corresponding variable in the simulator,
 * and the binding direction between the variables.
 */
class Var {
    string sim;
    double value;
    string direction;
public:
    Var(string simVar);
    ~Var();
    double getValue();
    void setValue(string val);
    void setDirection(string dir);
    string getDirection();
};

#endif //FLIGHT_SIMULATOR_VAR_H
