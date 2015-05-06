/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 */

#include <iostream>
#include <string>

#include "exp.h"
#include "parser.h"
#include "statement.h"

#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/lexicon.h"
using namespace std;

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression.
 */

Expression *parseExp(TokenScanner & scanner) {
   Expression *exp = readE(scanner);
   return exp;
}


// get an operator from scanner, if fails returns an empty string
string get_op(TokenScanner & scanner)
{
    string op = scanner.nextToken();
    if (op == "+" || op == "-" || op == "*" || op == "/"){
        return op;
    }else{
        scanner.saveToken(op);
        op = "";
        return op;
    }
}

bool is_keyword(string id)
{
    static Lexicon keyword("BasicKeywords.txt");
    return keyword.contains(id);
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int prec) {
   Expression *exp = readT(scanner);
   string token;
   while (true) {
      token = get_op(scanner);
      int newPrec = precedence(token);
      if (newPrec <= prec) break;
      Expression *rhs = readE(scanner, newPrec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner) {
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type == NUMBER) return new ConstantExp(stringToInteger(token));
   if (type == WORD && !is_keyword(token)) return new IdentifierExp(token);
   if (token != "(") error("SYNTAX ERROR");
   Expression *exp = readE(scanner);
   if (scanner.nextToken() != ")") {
      error("SYNTAX ERROR");
   }
   return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token) {
   //if (token == "=") return 1;
   if (token == "+" || token == "-") return 2;
   if (token == "*" || token == "/") return 3;
   return 0;
}

//read a name
string parseName(TokenScanner & scanner)
{
    string token = scanner.nextToken();
    if ((scanner.getTokenType(token) != WORD) || is_keyword(token)){
        error("SYNTAX ERROR");
    }
    return token;
}

//read a let statement (after the let keyword)
LetStatement * parseLet(TokenScanner & scanner)
{
    string name = parseName(scanner);
    string token = scanner.nextToken();
    if (token != "="){
        error("SYNTAX ERROR");
    }
    Expression * exp = parseExp(scanner);
    if (scanner.hasMoreTokens()){
        error("SYNTAX ERROR");
    }
    LetStatement * stmt = new LetStatement(name, exp);
    return stmt;
}

//read a input statement (after the input keyword)
InputStatement * parseInput(TokenScanner & scanner)
{
    string name = parseName(scanner);
    if (scanner.hasMoreTokens()){
        error("SYNTAX ERROR");
    }
    InputStatement * stmt = new InputStatement(name);
    return stmt;
}

//read a print statement (after the print keyword)
PrintStatement * parsePrint(TokenScanner & scanner)
{
    Expression * exp = parseExp(scanner);
    if (scanner.hasMoreTokens()){
        error("SYNTAX ERROR");
    }
    PrintStatement * stmt = new PrintStatement(exp);
    return stmt;
}

//parse a direct executed statement
Statement * parseDirect(TokenScanner & scanner)
{
    string token = scanner.nextToken();
    if (token == "LET") return parseLet(scanner);
    if (token == "INPUT") return parseInput(scanner);
    if (token == "PRINT") return parsePrint(scanner);
    error("SYNTAX ERROR");
}
