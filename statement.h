/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class LetStatement : public Statement
{
    public:
/*
 * Constructor: LetStatement
 * ----------------------
 * The constructor initializes a let statement from a name and an
 * expression.
 */

   LetStatement(std::string init_name, Expression * init_exp);

/*
 * Destructor: ~LetStatement
 * Usage: delete let_stmt;
 * -------------------
 * The destructor deallocates the storage for this statement.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~LetStatement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 *  execute a let statement will perform the assignment
 */

   virtual void execute(EvalState & state);

    private:
        std::string name;
        Expression * exp;
};

class RemStatement : public Statement
{
    public:
/*
 * Constructor: RemStatement
 * ----------------------
 * The constructor initializes a rem statement
 */

   RemStatement();

/*
 * Destructor: ~RemStatement
 * Usage: delete rem_stmt;
 * -------------------
 * The destructor deallocates the storage for this statement.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~RemStatement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 *  execute a rem will do nothing
 */

   virtual void execute(EvalState & state);

};

class InputStatement : public Statement
{
    public:
/*
 * Constructor: IntputStatement
 * ----------------------
 * The constructor initializes a input statement from a name
 */

   InputStatement(std::string init_name);

/*
 * Destructor: ~InputStatement
 * Usage: delete input_stmt;
 * -------------------
 * The destructor deallocates the storage for this statement.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~InputStatement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 *  execute a input statement will read a variable
 */

   virtual void execute(EvalState & state);

    private:
        std::string name;
};

class PrintStatement : public Statement
{
    public:
/*
 * Constructor: PrintStatement
 * ----------------------
 * The constructor initializes a let statement from an
 * expression.
 */

   PrintStatement(Expression * init_exp);

/*
 * Destructor: ~PrintStatement
 * Usage: delete print_stmt;
 * -------------------
 * The destructor deallocates the storage for this statement.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~PrintStatement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 *  execute a print statement will print the result of the expression
 */

   virtual void execute(EvalState & state);

    private:
        Expression * exp;
};

class EndStatement : public Statement
{
    public:
/*
 * Constructor: EndStatement
 * ----------------------
 * The constructor initializes a end statement
 */

   EndStatement();

/*
 * Destructor: ~EndStatement
 * Usage: delete end_stmt;
 * -------------------
 * The destructor deallocates the storage for this statement.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~EndStatement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 *  execute a end will halt the program
 */

   virtual void execute(EvalState & state);

};

class GotoStatement : public Statement
{
    public:
/*
 * Constructor: GotoStatement
 * ----------------------
 * The constructor initializes a goto statement from an
 * line number.
 */

   GotoStatement(LineNumber * ln);

/*
 * Destructor: ~GotoStatement
 * Usage: delete goto_stmt;
 * -------------------
 * The destructor deallocates the storage for this statement.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~GotoStatement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 *  set the program counter to the right value
 */

   virtual void execute(EvalState & state);

    private:
        LineNumber * line_number;
};

class IfStatement : public Statement
{
    public:
/*
 * Constructor: IfStatement
 * ----------------------
 * The constructor initializes a if statement from a BoolExp and a
 * line number.
 */

   IfStatement(BoolExp * exp, LineNumber * ln);

/*
 * Destructor: ~IfStatement
 * Usage: delete if_stmt;
 * -------------------
 * The destructor deallocates the storage for this statement.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~IfStatement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 *  set the program counter to the right value
 */

   virtual void execute(EvalState & state);

    private:
        LineNumber * line_number;
        BoolExp * cond;
};
#endif
