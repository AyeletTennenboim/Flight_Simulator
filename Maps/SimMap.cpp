#include <iostream>
#include "SimMap.h"

SimMap* SimMap::instance;

/**
 * Constructor:
 * The constructor creates a new Var object for each variable from the simulator
 * and inserts the variable name and its object to a map.
 */
SimMap::SimMap() {
    insertVar("/instrumentation/airspeed-indicator/indicated-speed-kt",new Var("/instrumentation/airspeed-indicator/indicated-speed-kt"));
    insertVar("/sim/time/warp", new Var("/sim/time/warp"));
    insertVar("/controls/switches/magnetos", new Var("/controls/switches/magnetos"));
    insertVar("/instrumentation/heading-indicator/offset-deg", new Var("/instrumentation/heading-indicator/offset-deg"));
    insertVar("/instrumentation/altimeter/indicated-altitude-ft", new Var("/instrumentation/altimeter/indicated-altitude-ft"));
    insertVar("/instrumentation/altimeter/pressure-alt-ft",new Var("/instrumentation/altimeter/pressure-alt-ft"));
    insertVar("/instrumentation/attitude-indicator/indicated-pitch-deg",new Var("/instrumentation/attitude-indicator/indicated-pitch-deg"));
    insertVar("/instrumentation/attitude-indicator/indicated-roll-deg",new Var("/instrumentation/attitude-indicator/indicated-roll-deg"));
    insertVar("/instrumentation/attitude-indicator/internal-pitch-deg",new Var("/instrumentation/attitude-indicator/internal-pitch-deg"));
    insertVar("/instrumentation/attitude-indicator/internal-roll-deg", new Var("/instrumentation/attitude-indicator/internal-roll-deg"));
    insertVar("/instrumentation/encoder/indicated-altitude-ft", new Var("/instrumentation/encoder/indicated-altitude-ft"));
    insertVar("/instrumentation/encoder/pressure-alt-ft",new Var("/instrumentation/encoder/pressure-alt-ft"));
    insertVar("/instrumentation/gps/indicated-altitude-ft",new Var("/instrumentation/gps/indicated-altitude-ft"));
    insertVar("/instrumentation/gps/indicated-ground-speed-kt",new Var("/instrumentation/gps/indicated-ground-speed-kt"));
    insertVar("/instrumentation/gps/indicated-vertical-speed",new Var("/instrumentation/gps/indicated-vertical-speed"));
    insertVar("/instrumentation/heading-indicator/indicated-heading-deg",new Var("/instrumentation/heading-indicator/indicated-heading-deg"));
    insertVar("/instrumentation/magnetic-compass/indicated-heading-deg",new Var("/instrumentation/magnetic-compass/indicated-heading-deg"));
    insertVar("/instrumentation/slip-skid-ball/indicated-slip-skid",new Var("/instrumentation/slip-skid-ball/indicated-slip-skid"));
    insertVar("/instrumentation/turn-indicator/indicated-turn-rate", new Var("/instrumentation/turn-indicator/indicated-turn-rate"));
    insertVar("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", new Var("/instrumentation/vertical-speed-indicator/indicated-speed-fpm"));
    insertVar("/controls/flight/aileron",new Var("/controls/flight/aileron"));
    insertVar("/controls/flight/elevator",new Var("/controls/flight/elevator"));
    insertVar("/controls/flight/rudder",new Var("/controls/flight/rudder"));
    insertVar("/controls/flight/flaps",new Var("/controls/flight/flaps"));
    insertVar("/controls/engines/engine/throttle",new Var("/controls/engines/engine/throttle"));
    insertVar("/controls/engines/current-engine/throttle", new Var("/controls/engines/current-engine/throttle"));
    insertVar("/controls/switches/master-avionics",new Var("/controls/switches/master-avionics"));
    insertVar("/controls/switches/starter",new Var("/controls/switches/starter"));
    insertVar("/engines/active-engine/auto-start",new Var("/engines/active-engine/auto-start"));
    insertVar("/controls/flight/speedbrake",new Var("/controls/flight/speedbrake"));
    insertVar("/sim/model/c172p/brake-parking", new Var("/sim/model/c172p/brake-parking"));
    insertVar("/controls/engines/engine/primer",new Var("/controls/engines/engine/primer"));
    insertVar("/controls/engines/current-engine/mixture",new Var("/controls/engines/current-engine/mixture"));
    insertVar("/controls/switches/master-bat",new Var("/controls/switches/master-bat"));
    insertVar("/controls/switches/master-alt",new Var("/controls/switches/master-alt"));
    insertVar("/engines/engine/rpm",new Var("/engines/engine/rpm"));
}

/**
 * Destructor:
 * The destructor deletes all the simulator Var objects.
 */
SimMap::~SimMap() {
    for (unordered_map <string, Var*>::iterator it = this->simMap.begin();
         it != this->simMap.end(); ++it) {
        if (it->second != nullptr) {
            delete it->second;
            it->second = nullptr;
        }
    }
}

/**
 * The function returns an instance of SimMap.
 *
 * @return instance of SimMap.
 */
SimMap* SimMap::getInstance() {
    // If there is no SimMap
    if (instance == nullptr) {
        // Create SimMap
        instance = new SimMap();
    }
    return instance;
}

/**
 * The function inserts a variable name and its object to the SimMap.
 *
 * @param var variable name.
 * @param value Var object.
 */
void SimMap::insertVar(string var, Var* value) {
    this->simMap.insert(make_pair(var, value));
}

/**
 * The function sets the value of a simulator Var object.
 *
 * @param var variable name.
 * @param val Var object.
 */
void SimMap::setValue(string var, string val) {
    if (this->simMap.find(var) != this->simMap.end()) {
        this->simMap.find(var)->second->setValue(val);
    } else {
        throw "Variable does not exist in SimMap";
    }
}

/**
 * The function returns a Var object from the map.
 *
 * @param var variable name.
 * @return Var object.
 */
Var* SimMap::getVarObject(string var) {
    if (this->simMap.find(var) != this->simMap.end()) {
        return this->simMap.find(var)->second;
    } else {
        throw "Variable does not exist in SimMap";
    }
}