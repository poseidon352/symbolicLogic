#ifndef _BOOLEANEXPRESSION_H_
#define _BOOLEANEXPRESSION_H_

#include "Parser.h"



class booleanExpression {
public:

    /**
     * Copy constructor for a booleanExpression.
     *
     * @param other The booleanExpression we are copying.
     */
    booleanExpression(const booleanExpression& other);

    /**
     * booleanExpression destructor.
     */
    ~booleanExpression();

    /**
     * Overloaded assignment operator for booleanExpression.
     *
     * @param rhs The right hand side of the assignment statement.
     */
    booleanExpression& operator=(const booleanExpression& rhs);


    /**
     * Constructor that builds a booleanExpression from a given string.
     * Ignoring whitespace, every symbol becomes a Node in the tree.
     * A capital letter represents a VAR, which is a leaf Node.
     * A ~ represents the NOT operator, whose right child is NULL.
     * All other valid symbol (&, |, ->, <->)represents the other 
     * operators, which have non-NULL children.
     * 
     * @param expression String representation of expression
     */
    booleanExpression(string &expression);


private:

    // Root of the Abstract Syntax Tree
    Node* root;
};


#endif