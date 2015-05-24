/*
 * File: Basic.cpp
 * ---------------
 * Name: 张宇宁
 * Section: 张宇宁
 * Yet another basic interpreter.
 * Online document: http://tcloud.sjtu.edu.cn:18000/courses/se/SE106/2015_spr/courseware/0b7ba5b85a7f44b3991e3dd071af31c1/ba037c80b87a49578bafa61552d6193e/
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
//#include "../StanfordCPPLib/lexicon.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   //init
   EvalState state;
   Program program;
   //Loop . Print . Eval . Read

   //loop
   while (true) {
      try {
         string input = getLine();
         if (!cin){
             cout << "fatal error: input fail!" << endl;
             exit(0);
         }
         processLine(input, program, state);
      } catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user. In this version,
 * it can respond correctly when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
   //setup
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);

   if (!scanner.hasMoreTokens()){ //empty input
       return;
   }

   string token = scanner.nextToken();
   if (scanner.getTokenType(token) == NUMBER){  //must be a line number
       int ln = str2int(token);
       if (ln >= 0){
           if (scanner.hasMoreTokens()){  //add line
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
   //direct execute
   if (token == "LET" || token == "INPUT" || token == "PRINT"){
       scanner.saveToken(token);
       Statement * stmt = parseDirect(scanner);
       stmt->execute(state);
       delete stmt;
       return;
   }
   //interpreter commands
   if (scanner.hasMoreTokens()){ //fix the bug
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
       cout << "Yet another basic interpreter" << endl;
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
