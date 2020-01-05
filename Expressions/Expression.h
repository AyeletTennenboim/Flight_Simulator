#ifndef FLIGHT_SIMULATOR_EXPRESSION_H
#define FLIGHT_SIMULATOR_EXPRESSION_H

#include "Expression.h"
#include <string>
#include <map>
#include <stack>

using namespace std;

/**
 * Expression Interface
 */
class Expression {
public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

/**
 * BinaryOperator Class
 */
class BinaryOperator : public Expression {
protected:
    Expression *leftExp = nullptr;
    Expression *rightExp = nullptr;
public:
    virtual ~BinaryOperator();
};

/**
 * Plus Class
 */
class Plus : public BinaryOperator {
public:
    Plus(Expression *left, Expression *right);
    virtual double calculate();
    virtual ~Plus();
};

/**
 * Minus Class
 */
class Minus : public BinaryOperator {
public:
    Minus(Expression *left, Expression *right);
    virtual double calculate();
    virtual ~Minus();
};

/**
 * Mul Class
 */
class Mul : public BinaryOperator {
public:
    Mul(Expression *left, Expression *right);
    virtual double calculate();
    virtual ~Mul();
};

/**
 * Div Class
 */
class Div : public BinaryOperator {
public:
    Div(Expression *left, Expression *right);
    virtual double calculate();
    virtual ~Div();
};

/**
 * Value Class
 */
class Value : public Expression {
    double value;
public:
    Value(double val);
    virtual double calculate();
    virtual ~Value();
};

/**
 * Variable Class
 */
class Variable : public Expression {
    string name;
    double value;
public:
    Variable(string name, double value);
    virtual double calculate();
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double add);
    Variable& operator-=(double sub);
    Variable& operator++(int);
    Variable& operator--(int);
    virtual ~Variable();
};

/**
 * UnaryOperator Class
 */
class UnaryOperator : public Expression {
protected:
    Expression *exp = nullptr;
public:
    virtual ~UnaryOperator();
};

/**
 * UPlus Class
 */
class UPlus : public UnaryOperator {
public:
    UPlus(Expression *ex);
    virtual double calculate();
    virtual ~UPlus();
};

/**
 * UMinus Class
 */
class UMinus : public UnaryOperator {
public:
    UMinus(Expression *ex);
    virtual double calculate();
    virtual ~UMinus();
};

/**
 * ‫‪Interpreter‬‬ Class
 */
class Interpreter {
    map<string, double> varMap;
    stack<string> operators;
    stack<Expression*> operands;
public:
    Interpreter();
    Expression* interpret(string str);
    void createNewExpression(int bracket);
    void setVariables(string vars);
    void isVarsFormatValid(string vars);
    void isVarNameValid(string name);
    void isInterpretInputValid(string input);
    ~Interpreter();
};

#endif //FLIGHT_SIMULATOR_EXPRESSION_H