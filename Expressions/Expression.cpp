#include "Expression.h"
#include "../Maps/SymbolTable.h"
#include <deque>
#include <regex>

using namespace std;

/*
 * BinaryOperator
 */

/// Destructor
BinaryOperator::~BinaryOperator() {
    if (leftExp != nullptr) {
        delete leftExp;
    }
    if (rightExp != nullptr) {
        delete rightExp;
    }
}

/*
 * Plus
 */

/// Constructor
Plus::Plus(Expression *left, Expression *right) {
    this->leftExp = left;
    this->rightExp = right;
}

/// Calculate
double Plus::calculate() {
    return this->leftExp->calculate() + this->rightExp->calculate();
}

/// Destructor
Plus::~Plus() {}

/*
 * Minus
 */

/// Constructor
Minus::Minus(Expression *left, Expression *right) {
    this->leftExp = left;
    this->rightExp = right;
}

/// Calculate
double Minus::calculate() {
    return this->leftExp->calculate() - this->rightExp->calculate();
}

/// Destructor
Minus::~Minus() {}

/*
 * Mul
 */

/// Constructor
Mul::Mul(Expression *left, Expression *right) {
    this->leftExp = left;
    this->rightExp = right;
}

/// Calculate
double Mul::calculate() {
    return this->leftExp->calculate() * this->rightExp->calculate();
}

/// Destructor
Mul::~Mul() {}

/*
 * Div
 */

/// Constructor
Div::Div(Expression *left, Expression *right) {
    this->leftExp = left;
    this->rightExp = right;
}

/// Calculate
double Div::calculate() {
    if (this->rightExp->calculate() == 0) {
        throw "Error! Division by zero";
    } else {
        return this->leftExp->calculate() / this->rightExp->calculate();
    }
}

/// Destructor
Div::~Div() {}

/*
 * Value
 */

/// Constructor
Value::Value(double val) {
    this->value = val;
}

/// Calculate
double Value::calculate() {
    return this->value;
}

/// Destructor
Value::~Value() {}

/*
 * Variable
 */

/// Constructor
Variable::Variable(string nameS, double valueD) {
    this->name = nameS;
    this->value = valueD;
}

/// Calculate
double Variable::calculate() {
    return this->value;
}

/// ++ operator
Variable& Variable::operator++() {
    ++this->value;
    return *this;
}

/// -- operator
Variable& Variable::operator--() {
    --this->value;
    return *this;
}

/// += operator
Variable& Variable::operator+=(double add) {
    this->value += add;
    return *this;
}

/// -= operator
Variable& Variable::operator-=(double sub) {
    this->value -= sub;
    return *this;
}

/// ++ operator
Variable& Variable::operator++(int) {
    ++this->value;
    return *this;
}

/// -- operator
Variable& Variable::operator--(int) {
    --this->value;
    return *this;
}

/// Destructor
Variable::~Variable() {}

/*
 * UnaryOperator
 */

/// Destructor
UnaryOperator::~UnaryOperator() {
    if (exp != nullptr) {
        delete exp;
    }
}

/*
 * UPlus
 */

/// Constructor
UPlus::UPlus(Expression *ex) {
    this->exp = ex;
}

/// Calculate
double UPlus::calculate() {
    return this->exp->calculate();
}

/// Destructor
UPlus::~UPlus() {}

/*
 * UMinus
 */

/// Constructor
UMinus::UMinus(Expression *ex) {
    this->exp = ex;
}

/// Calculate
double UMinus::calculate() {
    return -(this->exp->calculate());
}

/// Destructor
UMinus::~UMinus() {}

/*
 * Interpreter
 */

/// Constructor
Interpreter::Interpreter() {}

/// Destructor
Interpreter::~Interpreter() {}

/**
 * The function inserts the variables and their value in a map.
 *
 * @param vars a string of variables.
 */
void Interpreter::setVariables(string vars) {
    string varStr = vars;
    vector<string> resultMid;
    vector<string> resultFinal;
    string token;
    // Check if the input format is valid
    isVarsFormatValid(varStr);
    // Separate varStr by the delimiter ';'
    stringstream ss(varStr);
    while (getline(ss, token, ';')) {
        resultMid.push_back(token);
    }
    // Separate by the delimiter '='
    for (string str : resultMid) {
        stringstream sts(str);
        while (getline(sts, token, '=')) {
            resultFinal.push_back(token);
        }
    }
    // Go over the vector that contains variables and values separately
    for (unsigned int i = 0; i < resultFinal.size(); i += 2) {
        // Check if the variable name is valid
        isVarNameValid(resultFinal[i]);
        // If the variable already exists in the map
        if (this->varMap.count(resultFinal[i])) {
            try {
                // Change its value
                varMap[resultFinal[i]] = stod(resultFinal[i + 1]);
            } catch (exception& e) {
                throw "Error! Invalid variable assignment";
            }
        } else {
            try {
                // Insert the variable name and its value as a key and value into the map
                this->varMap.insert({resultFinal[i], stod(resultFinal[i + 1])});
            } catch (exception& e) {
                throw "Error! Invalid variable assignment";
            }
        }
    }
}

/**
 * The function checks if the input format is valid (name=value;name=value..)
 *
 * @param vars a string of variables.
 */
void Interpreter::isVarsFormatValid(string vars) {
    string varStr = vars;
    int validFormat = 0;
    // Convert the varStr string to varArr array of chars
    const char *varArr = varStr.c_str();
    for (unsigned int j = 0; j < varStr.size(); j++) {
        if (varArr[j] == '=') {
            validFormat++;
        } else if (varArr[j] == ';') {
            validFormat--;
        }
        if (validFormat < 0 || validFormat > 1) {
            throw "Error! Invalid variables expression";
        }
    }
    if (validFormat != 1) {
        throw "Error! Invalid variables expression";
    }
}

/**
 * The function checks if the variable name is valid.
 *
 * @param name the variable name.
 */
void Interpreter::isVarNameValid(string name) {
    string varName = name;
    // Convert the varName string to nameArr array of chars
    const char *nameArr = varName.c_str();
    for (unsigned int i = 0; i < varName.size(); i++) {
        if (!((nameArr[i] >= 'a' && nameArr[i] <= 'z') || (nameArr[i] >= 'A' && nameArr[i] <= 'Z')
              || (nameArr[i] >= '0' && nameArr[i] <= '9') || (nameArr[i] == '_'))) {
            throw "Error! Invalid variable name";
        }
    }
    if (nameArr[0] >= '0' && nameArr[0] <= '9') {
        throw "Error! Invalid variable name";
    }
}

/**
 * The function receives a string of expression
 * and returns a pointer to an expression object.
 *
 * @param str a string of expression.
 * @return expression object.
 */
Expression* Interpreter::interpret(string str) {
    string infix = str;
    // Remove spaces
    infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
    Expression* operand = nullptr;
    // Instance of the SymbolTable
    SymbolTable* symbolTable = SymbolTable::getInstance();
    // Indication if the current char is the first char of the string or if the previous char was '('
    int flag = 1;
    // Check if the input string to interpret is valid
    isInterpretInputValid(infix);
    regex delimiters(R"(\+|-|\*|/|\(|\))");
    // Separate the string by operators
    sregex_token_iterator srti(infix.begin(), infix.end(), delimiters, {-1, 0});
    vector<string> tokens;
    remove_copy_if(srti, sregex_token_iterator(), back_inserter(tokens),
                   [](string const &s) { return s.empty(); });
    // Push each token into the appropriate stack
    for (auto &token : tokens) {
        // Uses overloaded operator== to compare string values
        if (token == "-") {
            if (flag == 1) {
                // A symbol for UMinus operator
                this->operators.push("#");
                flag = 0;
            } else {
                if (!this->operators.empty() && (this->operators.top() == "*" || this->operators.top() == "/"
                                                 || this->operators.top() == "#" || this->operators.top() == "$")) {
                    createNewExpression(0);
                }
                this->operators.push(token);
            }
        } else if (token == "+") {
            if (flag == 1) {
                // A symbol for UPlus operator
                this->operators.push("$");
                flag = 0;
            } else {
                if (!this->operators.empty() && (this->operators.top() == "*" || this->operators.top() == "/"
                     || this->operators.top() == "#" || this->operators.top() == "$" || this->operators.top() == "-")) {
                    createNewExpression(0);
                }
                this->operators.push(token);
            }
        } else if (token == "*" || token == "/") {
            if (!this->operators.empty() && (this->operators.top() == "#" || this->operators.top() == "$")) {
                createNewExpression(0);
            }
            this->operators.push(token);
            flag = 0;
        } else if (token == "(") {
            this->operators.push(token);
            flag = 1;
        } else if (token == ")") {
            createNewExpression(1);
        } else {
            // If the token is a number
            try {
                operand = new Value(stod(token));
                // If the token is a variable
            } catch (exception& e) {
                // If the variable exists in the SymbolTable
                if (symbolTable->isVarExists(token)) {
                    operand = new Variable(token, symbolTable->getVarValue(token));
                } else {
                    throw "Error! Use of a non-existent variable";
                }
            }
            this->operands.push(operand);
            flag = 0;
        }
    }
    while (!this->operators.empty()) {
        createNewExpression(0);
    }
    return this->operands.top();
}

/**
 *  The function creates new expression according to an operator
 *  and pushes it to the operands stack.
 *
 *  @param bracket indication if the function was called because of a bracket.
 */
void Interpreter::createNewExpression(int bracket) {
    char topOperator = this->operators.top().c_str()[0];
    Expression* leftOperand = nullptr;
    Expression* rightOperand = nullptr;
    switch (topOperator) {
        case '+':
            rightOperand = this->operands.top();
            this->operands.pop();
            leftOperand = this->operands.top();
            this->operands.pop();
            this->operands.push(new Plus(leftOperand, rightOperand));
            break;
        case '-':
            rightOperand = this->operands.top();
            this->operands.pop();
            leftOperand = this->operands.top();
            this->operands.pop();
            this->operands.push(new Minus(leftOperand, rightOperand));
            break;
        case '*':
            rightOperand = this->operands.top();
            this->operands.pop();
            leftOperand = this->operands.top();
            this->operands.pop();
            this->operands.push(new Mul(leftOperand, rightOperand));
            break;
        case '/':
            rightOperand = this->operands.top();
            this->operands.pop();
            leftOperand = this->operands.top();
            this->operands.pop();
            this->operands.push(new Div(leftOperand, rightOperand));
            break;
        case '#':
            rightOperand = this->operands.top();
            this->operands.pop();
            this->operands.push(new UMinus(rightOperand));
            break;
        case '$':
            rightOperand = this->operands.top();
            this->operands.pop();
            this->operands.push(new UPlus(rightOperand));
            break;
        case '(':
            this->operators.push("(");
        default:
            break;
    }
    this->operators.pop();
    // If the function was called because of a bracket ')'
    if (bracket) {
        // Pop the other bracket '('
        this->operators.pop();
    }
    if (!operators.empty() && this->operators.top().c_str()[0] == '#') {
        rightOperand = this->operands.top();
        this->operands.pop();
        this->operands.push(new UMinus(rightOperand));
        this->operators.pop();
    } else if (!operators.empty() && this->operators.top().c_str()[0] == '$') {
        rightOperand = this->operands.top();
        this->operands.pop();
        this->operands.push(new UPlus(rightOperand));
        this->operators.pop();
    }
}

/**
 * The function checks if the input string to interpret is valid.
 *
 * @param input string to interpret.
 */
void Interpreter::isInterpretInputValid(string input) {
    string inputStr = input;
    int validBrackets = 0;
    int inputSize = inputStr.size();
    // Convert the inputStr string to inputArr array of chars
    const char *inputArr = inputStr.c_str();
    // Check if the first char is an unary operator or ')'
    if (inputArr[0] == '*' || inputArr[0] == '/' || inputArr[0] == ')') {
        throw "Error! Invalid math expression";
    }
    // Check if the last char is an unary operator or '('
    if (inputArr[inputSize - 1] == '+' || inputArr[inputSize - 1] == '-' || inputArr[inputSize - 1] == '*'
        || inputArr[inputSize - 1] == '/' || inputArr[inputSize - 1] == '(') {
        throw "Error! Invalid math expression";
    }
    for (int i = 0; i < inputSize; i++) {
        // Check if the input contains an invalid char
        if (!((inputArr[i] >= 'a' && inputArr[i] <= 'z') || (inputArr[i] >= 'A' && inputArr[i] <= 'Z')
              || (inputArr[i] >= '0' && inputArr[i] <= '9') || (inputArr[i] == '_') || (inputArr[i] == '+')
              || (inputArr[i] == '-') || (inputArr[i] == '*') || (inputArr[i] == '/')
              || (inputArr[i] == '(') || (inputArr[i] == ')') || (inputArr[i] == '.'))) {
            throw "Error! Invalid math expression";
        }
        // Count the brackets
        if (inputArr[i] == '(') {
            validBrackets++;
        } else if (inputArr[i] == ')') {
            validBrackets--;
        }
        // Check if there is ')' without '(' before
        if (validBrackets < 0) {
            throw "Error! Invalid math expression";
        }
        // Check if there are two consecutive operators
        if ((i < inputSize - 1) && ((inputArr[i] == '+') || (inputArr[i] == '-')
                                    || (inputArr[i] == '*') || (inputArr[i] == '/'))) {
            if ((inputArr[i + 1] == '+') || (inputArr[i + 1] == '-')
                || (inputArr[i + 1] == '*') || (inputArr[i + 1] == '/')) {
                throw "Error! Invalid math expression";
            }
        }
        // Check if there is ')' without an operator or ')' after
        if ((i < inputSize - 1) && (inputArr[i] == ')')) {
            if (!((inputArr[i + 1] == '+') || (inputArr[i + 1] == '-') || (inputArr[i + 1] == '*')
                  || (inputArr[i + 1] == '/') || (inputArr[i + 1] == ')'))) {
                throw "Error! Invalid math expression";
            }
        }
        // Check if there is '(' without an operator or '(' before
        if ((i > 0) && (inputArr[i] == '(')) {
            if (!((inputArr[i - 1] == '+') || (inputArr[i - 1] == '-') || (inputArr[i - 1] == '*')
                  || (inputArr[i - 1] == '/') || (inputArr[i - 1] == '('))) {
                throw "Error! Invalid math expression";
            }
        }
        // Check if there are empty brackets
        if ((i < inputSize - 1) && (inputArr[i] == '(') && (inputArr[i + 1] == ')')) {
            throw "Error! Invalid math expression";
        }
    }
    // Check if there is '(' without ')' after
    if (validBrackets != 0) {
        throw "Error! Invalid math expression";
    }
}