/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC
 * program.
 */

#ifndef _program_h
#define _program_h

#include <string>
#include <map>
#include <memory>
#include "statement.h"
#include "evalstate.h"
using namespace std;

/*
 * This class represent a line of the program, consist of the origin line and the parsed AST
 */
class ProgramLine
{
    public:
        ProgramLine(string origin_line, Statement * parsed_ast);
        ProgramLine();
        //excute the line
        void execute(EvalState & state);
        //Show the line
        void show();
    private:
        //used smart pointer to handle the AST
        shared_ptr<Statement> stmt;
        string line;
};


/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    pointer to a Statement.
 */

class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */

   Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */

   ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */

   void clear();

/*
 * Method: addSourceLine
 * Usage: program.addSourceLine(lineNumber, line, ast);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the line replaces the old one.
 * if the line is new, it is added.
 */

   void addSourceLine(int lineNumber, std::string line, Statement * parsed_line);

/*
 * Method: removeSourceLine
 * Usage: program.removeSourceLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 */

   void removeSourceLine(int lineNumber);

/*
 * Method: list
 * Usage: program.list()
 * --------------------------------------------
 * Just list all the lines.
 */

   void list();

/*
 * Method: run
 * Usage: program.run()
 * ---------------------------------------------
 *  Run the program.
 */

   void run(EvalState & state);

private:

   //the map to store the code
   map<int, ProgramLine> code;

};

#endif
