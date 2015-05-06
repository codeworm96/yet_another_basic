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


