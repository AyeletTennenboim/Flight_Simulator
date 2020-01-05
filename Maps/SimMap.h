#ifndef FLIGHT_SIMULATOR_SIMMAP_H
#define FLIGHT_SIMULATOR_SIMMAP_H

#include "Var.h"
#include <string>
#include <unordered_map>

using namespace std;

/**
 * SimMap Class
 *
 * This class contains a map that links a name of a simulator variable
 * to a variable object.
 */
class SimMap {
    static SimMap *instance;
    unordered_map <string, Var*> simMap;
    SimMap();
public:
    static SimMap* getInstance();
    void  insertVar(string var, Var* value);
    void setValue(string var, string val);
    Var* getVarObject(string var);
    ~SimMap();
};

#endif //FLIGHT_SIMULATOR_SIMMAP_H
