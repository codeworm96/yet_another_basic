/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "program.h"
#include "statement.h"
#include "evalstate.h"
using namespace std;

ProgramLine::ProgramLine(string origin_line, Statement * parsed_line):line(origin_line), stmt(parsed_line) {}

ProgramLine::ProgramLine():line(""), stmt(nullptr) {}

ProgramLine::~ProgramLine() {}

void ProgramLine::show()
{
    cout << line << endl;
}

void ProgramLine::execute(EvalState & state)
{
    stmt->execute(state);
}

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
}

void Program::clear() {
    code.clear();
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

string Program::getSourceLine(int lineNumber) {
   return "";    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
   return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
   return 0;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
   return 0;     // Replace this stub with your own code
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
        state.setPC(EvalState::SEQUENTIAL);
        it->second.execute(state);
        int pc = state.getPC();
        if (pc == EvalState::HALT){
            return;
        }else{
            if (pc == EvalState::SEQUENTIAL){
                ++it;
            }else{
                it = code.find(pc);
                if (it == code.end()){
                    error("LINE NUMBER ERROR");
                }
            }
        }
    }
}
