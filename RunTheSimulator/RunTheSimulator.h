#ifndef FLIGHT_SIMULATOR_RUNTHESIMULATOR_H
#define FLIGHT_SIMULATOR_RUNTHESIMULATOR_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../Commands/Command.h"

using namespace std;

/**
 * RunTheSimulator Class
 *
 * This class is responsible for reading a file containing code
 * and executing commands according to the code.
 */
class RunTheSimulator {
public:
    RunTheSimulator();
    ~RunTheSimulator();
    vector<string> lexer(string file);
    void parser(vector<string> strArr);
};

#endif //FLIGHT_SIMULATOR_RUNTHESIMULATOR_H
