#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <queue>
#include "Node.h"

using namespace std;

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
     * @param expression String representation of expression
     */
    Parser(const string &expression);

    // Parse the expression into an AST
    Node* parse();

private:
    string expr;       // Input Boolean expression

    string removeAllWhitespace(const string& str);
    queue<string> infixToRpn();
    int operatorSize(int index);
    bool hasLeftAssociativity(string &op);
    int getPrecedence(string &op);
    Node* rpnToExpr(queue<string> &queue);
};

#endif