#ifndef FLIGHT_SIMULATOR_IFCOMMAND_H
#define FLIGHT_SIMULATOR_IFCOMMAND_H

#include "ConditionParser.h"

using namespace std;
/**
 * IfCommand Class
 *
 * This class implements the ConditionParser interface. It executes an If command.
 * It checks a condition and if it's true it executes all the commands in the scope.
 */
class IfCommand : public ConditionParser {
public:
    IfCommand();
    virtual ~IfCommand();
    virtual int execute(vector<string> &strArr, int index);
};

#endif //FLIGHT_SIMULATOR_IFCOMMAND_H