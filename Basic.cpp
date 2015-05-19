/*
 * File: Basic.cpp
 * ---------------
 * Name: 张宇宁
 * Section: 张宇宁
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "statement.h"
#include "program.h"
#include "utility.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/lexicon.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state, Lexicon & directStmt);

/* Main program */

int main() {
   EvalState state;
   Program program;
   Lexicon directStmt;
   directStmt.add("LET");
   directStmt.add("INPUT");
   directStmt.add("PRINT");
   while (true) {
      try {
         processLine(getLine(), program, state, directStmt);
      } catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state, directstmt);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state, Lexicon & directStmt) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   /*
   Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;
   delete exp;
   */
   if (!scanner.hasMoreTokens()){
       return;
   }
   string token = scanner.nextToken();
   if (scanner.getTokenType(token) == NUMBER){
       int ln = str2int(token);
       if (ln >= 0){
           if (scanner.hasMoreTokens()){
               Statement * stmt = parseStatement(scanner);
               program.addSourceLine(ln, line, stmt);
           }else{
               program.removeSourceLine(ln);
           }
       }else{
           error("SYNTAX ERROR");
       }
       return;
   }
   if (directStmt.contains(token)){
       scanner.saveToken(token);
       Statement * stmt = parseDirect(scanner);
       stmt->execute(state);
       delete stmt;
   }else{
       if (scanner.hasMoreTokens()){
           error("SYNTAX ERROR");
       }
       if (token == "QUIT")
       {
           exit(0);
           return;
       }
       if (token == "LIST"){
           program.list();
           return;
       }
       if (token == "HELP") {
           return;
       }
       if (token == "RUN")
       {
           program.run(state);
           return;
       }
       if (token == "CLEAR"){
           program.clear();
           state.clear();
           return;
       }
       error("SYNTAX ERROR");
   }
}
