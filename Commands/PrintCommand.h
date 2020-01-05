#ifndef FLIGHT_SIMULATOR_PRINTCOMMAND_H
#define FLIGHT_SIMULATOR_PRINTCOMMAND_H

#include "Command.h"

using namespace std;

/**
 * PrintCommand Class
 *
 * This class implements the Command interface.
 * It prints a string message or the result of calculating the expression it got.
 */
class PrintCommand : public Command {
    const int movement = 2;
public:
    PrintCommand();
    virtual ~PrintCommand();
    virtual int execute(vector<string> &strArr, int index);
};

#endif //FLIGHT_SIMULATOR_PRINTCOMMAND_H