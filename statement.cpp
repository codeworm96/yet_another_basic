/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "utility.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

/* Implementation of the let statement class */

LetStatement::LetStatement(std::string init_name, Expression * init_exp):name(init_name), exp(init_exp) {}

LetStatement::~LetStatement()
{
    if (exp)
        delete exp;
}

void LetStatement::execute(EvalState & state)
{
    int res = exp->eval(state);
    state.setValue(name, res);
}

/* Implementation of the RemStatement class */

RemStatement::RemStatement() {
   /* Empty */
}

RemStatement::~RemStatement() {
   /* Empty */
}

void RemStatement::execute(EvalState & state)
{
}

/* Implementation of the input statement class */

InputStatement::InputStatement(std::string init_name):name(init_name) {}

InputStatement::~InputStatement()
{
    /* Empty */
}

void InputStatement::execute(EvalState & state)
{
    int res = input_int();
    state.setValue(name, res);
}

/* Implementation of the print statement class */

PrintStatement::PrintStatement(Expression * init_exp):exp(init_exp) {}

PrintStatement::~PrintStatement()
{
    if (exp)
        delete exp;
}

void PrintStatement::execute(EvalState & state)
{
    int res = exp->eval(state);
    cout << res <<endl;
}

