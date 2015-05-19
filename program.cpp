/*
 * File: program.cpp
 * -----------------
 * This file is the implementation of the program.h interface.
 */

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "program.h"
#include "statement.h"
#include "evalstate.h"
using namespace std;

/* Implementation of the ProgramLine class */

ProgramLine::ProgramLine(string origin_line, Statement * parsed_line):line(origin_line), stmt(parsed_line) {}

ProgramLine::ProgramLine():line(""), stmt(nullptr) {}

void ProgramLine::show()
{
    cout << line << endl;
}

void ProgramLine::execute(EvalState & state)
{
    stmt->execute(state);
}

Program::Program() {
   // Empty 
}

Program::~Program() {
   // Empty 
}

void Program::clear() {
    code.clear(); //proxy the message to the map
}

void Program::addSourceLine(int lineNumber, string line, Statement * stmt) {
    code[lineNumber] = ProgramLine(line, stmt);
}

void Program::removeSourceLine(int lineNumber) {
    map<int, ProgramLine>::iterator it = code.find(lineNumber);
    if (it != code.end()){
        code.erase(it);
    }
}

void Program::list()
{
    map<int, ProgramLine>::iterator it = code.begin();
    while(it != code.end()){
        it->second.show();
        ++it;
    }
}

void Program::run(EvalState & state)
{
    map<int, ProgramLine>::iterator it = code.begin();
    while(it != code.end()){
        state.setPC(EvalState::SEQUENTIAL);  //default
        it->second.execute(state);
        int pc = state.getPC();
        if (pc == EvalState::HALT){          //end
            return;
        }else{
            if (pc == EvalState::SEQUENTIAL){
                ++it;
            }else{                           //jump
                it = code.find(pc);
                if (it == code.end()){
                    error("LINE NUMBER ERROR");
                }
            }
        }
    }
}
