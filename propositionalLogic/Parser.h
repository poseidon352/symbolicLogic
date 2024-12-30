#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <queue>
#include "Node.h"

class Parser {
public:

    /**
     * Constructor that builds a Parser for a given string.
     * Ignoring whitespace, every symbol becomes a Node in the tree.
     * A capital letter represents a VAR, which is a leaf Node.
     * A ~ represents the NOT operator, whose left child is NULL.
     * All other valid symbol (&, |, ->, <->) represents the other 
     * operators, which have non-NULL children.
     * 
     * @param expression String representation of expression.
     */
    Parser(const std::string &expression);

    /**
     * @return Root of the Abstract Syntax Tree (AST) produced
     */
    Node* parse();

private:
    std::string expr;       // Input propositional logic expression

    /**
     * @return Copy of input string with all whitespace removed.
     */
    std::string removeAllWhitespace(const std::string& str);

    /**
     * Converts string representation of expression from infix notation
     * to Reverse Polish Notation using the Shunting Yard Algorithm.
     * @return Queue of string representation of symbols in rpn format.
     */
    std::queue<std::string> infixToRpn();

    /**
     * @param index Index of the beginning of the desired operator in expr.
     * @return Number of characters in the string of the operator, if not 
     * a valid operator then returns -1.
     */
    int operatorSize(int index);

    /**
     * @param op String of a propositional logic operator.
     * @return Whether or not the operator has left associativity.
     */
    bool hasLeftAssociativity(std::string &op);

    /**
     * If parentheses are not present to seperate operators then
     * the expression is parsed according to each operator's precedence.
     * @param op String of a propositional logic operator.
     * @return Integer representing the operator's priority when parsed.
     */
    int getPrecedence(std::string &op);

    /**
     * @todo Write description of function
     * 
     * @param queue Queue of string representation of symbols in rpn format.
     * @return Root of the AST produced original input string.
     */
    Node* rpnToExpr(std::queue<std::string> &queue);
};

#endif