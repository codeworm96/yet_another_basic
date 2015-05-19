/*
 * File: evalstate.h
 * -----------------
 * This interface exports a class called EvalState, which keeps track
 * of additional information required by the evaluator, most notably
 * the values of variables.
 */

#ifndef _evalstate_h
#define _evalstate_h

#include <string>
#include "../StanfordCPPLib/map.h"

/*
 * Class: EvalState
 * ----------------
 * This class is passed by reference through the recursive levels
 * of the evaluator and contains information from the evaluation
 * environment that the evaluator may need to know.  In this
 * version, the information maintained by the EvalState class
 * is a symbol table that maps variable names into their values and a
 * program counter.
 */

class EvalState {

public:

    static const int SEQUENTIAL = -1;  //Special Line Number for sequential executive;
    static const int HALT = -2;  //Special Line Number for halting;


/*
 * Constructor: EvalState
 * Usage: EvalState state;
 * -----------------------
 * Creates a new EvalState object with no variable bindings.
 */

   EvalState();

/*
 * Destructor: ~EvalState
 * Usage: usually implicit
 * -----------------------
 * Frees all heap storage associated with this object.
 */

   ~EvalState();

/*
 * Method: setValue
 * Usage: state.setValue(var, value);
 * ----------------------------------
 * Sets the value associated with the specified var.
 */

   void setValue(std::string var, int value);

/*
 * Method: getValue
 * Usage: int value = state.getValue(var);
 * ---------------------------------------
 * Returns the value associated with the specified variable.
 */

   int getValue(std::string var);

/*
 * Method: isDefined
 * Usage: if (state.isDefined(var)) . . .
 * --------------------------------------
 * Returns true if the specified variable is defined.
 */

   bool isDefined(std::string var);

/*
 * Method: setPC
 * Usage: state.setPC(line_number);
 * ----------------------------------
 * Sets the program counter to $line_number.
 */

   void setPC(int line_number);

/*
 * Method: getPC
 * Usage: int line_number = state.getPC();
 * ---------------------------------------
 * Returns the program counter.
 */

   int getPC();
/*
 * Method: clear
 * Usage: evalstate.clear()
 * ---------------------------------------
 * Clears all the status
 */

   void clear();

private:

   int program_counter; //store the address of the next instruction
   Map<std::string,int> symbolTable;

};

#endif
