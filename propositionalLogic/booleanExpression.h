#ifndef _BOOLEANEXPRESSION_H_
#define _BOOLEANEXPRESSION_H_

#include "Parser.h"



class booleanExpression {
public:

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
    booleanExpression(std::string &expression);


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
     * 
     */
    bool evaluate(const std::map<char, bool>& vars) const;

private:
    // Root of the Abstract Syntax Tree
    Node* root;

    /**
     * Copies the parameter other quadtree into the current booleanExpression.
     * Called by copy constructor and operator=.
     * @param other The booleanExpression to be copied.
     */
    void copy(const booleanExpression& other);

    /**
     * Private helper function for copy. Recursively copies
     * all of other data into new booleanExpression
     * @param other Node to copy.
     * @param parent parent of the Node to copy
     * @return Copied Node
     **/
    Node* copyNode(const Node* other, Node* parent);

    /**
     * Destroys all dynamically allocated memory associated with the
     * current booleanExpression.
     */
    void clear(Node* &node);
};


#endif