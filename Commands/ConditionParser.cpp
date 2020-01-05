#include "ConditionParser.h"

/**
 * The function checks if condition is true or false.
 *
 * @param left left expression in the condition.
 * @param sign operator </>/<=/>=/==/!=
 * @param right right expression in the condition.
 * @return true if the condition is true, false if not.
 */
bool ConditionParser::conditionIsTrue(string& left, string& sign, string& right) {
    bool isTrue;
    Interpreter* i = new Interpreter();
    Expression* leftExp = nullptr;
    Expression* rightExp = nullptr;
    try {
        // Interpret the left expression in condition
        leftExp = i->interpret(left);
        // Interpret the right expression in condition
        rightExp = i->interpret(right);
        // If the sign is < - return if the left expression is smaller than the right expression
        if (sign == "<") {
            isTrue = (leftExp->calculate() < rightExp->calculate());
        // If the sign is > - return if the left expression is bigger than the right expression
        } else if (sign == ">") {
            isTrue = (leftExp->calculate() > rightExp->calculate());
        // If the sign is <= - return if the left expression is smaller/equals to the right expression
        } else if (sign == "<=") {
            isTrue = (leftExp->calculate() <= rightExp->calculate());
        // If the sign is >= - return if the left expression is bigger/equals to the right expression
        } else if (sign == ">=") {
            isTrue = (leftExp->calculate() >= rightExp->calculate());
        // If the sign is == - return if the left expression is equals to the right expression
        } else if (sign == "==") {
            isTrue = (leftExp->calculate() == rightExp->calculate());
        // If the sign is != - return if the left expression is different from the right expression
        } else {
            isTrue = (leftExp->calculate() != rightExp->calculate());
        }
        delete i;
        delete leftExp;
        delete rightExp;
        return isTrue;
    // Catch if the interpretation throws an exception
    } catch (const char* e) {
        delete i;
        delete leftExp;
        delete rightExp;
        cout << e << endl;
        exit(-1);
    }
}