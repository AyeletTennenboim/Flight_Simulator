#ifndef FLIGHT_SIMULATOR_CONDITIONPARSER_H
#define FLIGHT_SIMULATOR_CONDITIONPARSER_H

#include <iostream>
#include "Command.h"
#include "../Expressions/Expression.h"

using namespace std;

/**
 * ConditionParser Class
 *
 * This class implements the Command interface. It is an interface for commands like
 * loops and conditions that need to execute a series of commands.
 * The class has a "conditionIsTrue" method. Its purpose is to check a condition
 * and returns true or false. If it returns true, the program executes the series
 * of commands that in this scope.
 */
class ConditionParser : public Command {
protected:
    int movement;
public:
    virtual ~ConditionParser() {}
    virtual int execute(vector<string> &strArr, int index) = 0;
    bool conditionIsTrue(string& left, string& sign, string& right);
};

#endif //FLIGHT_SIMULATOR_CONDITIONPARSER_H