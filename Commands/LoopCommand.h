#ifndef FLIGHT_SIMULATOR_LOOPCOMMAND_H
#define FLIGHT_SIMULATOR_LOOPCOMMAND_H

#include "ConditionParser.h"

using namespace std;

/**
 * LoopCommand Class
 *
 * This class implements the ConditionParser interface. It executes a While command.
 * At each iteration it checks a condition and if the condition is true, it executes
 * all the commands in the scope. It does that till the condition is false.
 */
class LoopCommand : public ConditionParser {
public:
    LoopCommand();
    virtual ~LoopCommand();
    virtual int execute(vector<string> &strArr, int index);
};

#endif //FLIGHT_SIMULATOR_LOOPCOMMAND_H