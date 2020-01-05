#ifndef FLIGHT_SIMULATOR_COMMAND_H
#define FLIGHT_SIMULATOR_COMMAND_H

#include <string>
#include <vector>

using namespace std;

/**
 * Command Interface
 *
 * This class is an interface with a method execute().
 * Each command in the program is a Command type class.
 * It means Command is polymorphic and can be any specific command
 * so all commands can be run in the same way.
 */
class Command {
public:
    virtual int execute(vector<string> &strArr, int index) = 0;
    virtual ~Command() {}
};

#endif //FLIGHT_SIMULATOR_COMMAND_H