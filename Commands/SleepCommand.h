#ifndef FLIGHT_SIMULATOR_SLEEPCOMMAND_H
#define FLIGHT_SIMULATOR_SLEEPCOMMAND_H

#include "Command.h"

using namespace std;

/**
 * SleepCommand Class
 *
 * This class implements the Command interface. It makes the main thread sleeps for
 * a time that set by interpreting and calculating an expression received as a parameter
 * of Sleep command.
 */
class SleepCommand : public Command {
    const int movement = 2;
public:
    SleepCommand();
    virtual ~SleepCommand();
    virtual int execute(vector<string> &strArr, int index);
};

#endif //FLIGHT_SIMULATOR_SLEEPCOMMAND_H