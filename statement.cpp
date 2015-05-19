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
  /* Empty */
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
    delete exp;
}

void PrintStatement::execute(EvalState & state)
{
    int res = exp->eval(state);
    cout << res <<endl;
}

/* Implementation of the EndStatement class */

EndStatement::EndStatement() {
   /* Empty */
}

EndStatement::~EndStatement() {
   /* Empty */
}

void EndStatement::execute(EvalState & state)
{
    state.setPC(EvalState::HALT);
}

/* Implementation of the GotoStatement class */

GotoStatement::GotoStatement(LineNumber * ln) :line_number(ln) {}

GotoStatement::~GotoStatement() {
   delete line_number;
}

void GotoStatement::execute(EvalState & state)
{
    state.setPC(line_number->eval(state));
}

/* Implementation of the IfStatement class */

IfStatement::IfStatement(BoolExp * exp, LineNumber * ln):cond(exp), line_number(ln) {}

IfStatement::~IfStatement() {
   delete cond;
   delete line_number;
}

void IfStatement::execute(EvalState & state)
{
    bool res = cond->eval(state);
    if (res){
        state.setPC(line_number->eval(state));
    }
}
