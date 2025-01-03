#ifndef _BOOLEANEXPRESSION_H_
#define _BOOLEANEXPRESSION_H_

#include "Parser.h"
#include "TruthTable.h"
#include <set>


class booleanExpression {
public:
    TruthTable* table;
    /**
     * Constructor that builds a booleanExpression from a given string.
     * Ignoring whitespace, every symbol becomes a Node in the tree.
     * A capital letter represents a VAR, which is a leaf Node.
     * A ~ represents the NOT operator, whose right child is NULL.
     * All other valid symbol (&, |, ->, <->)represents the other 
     * operators, which have non-NULL children.
     * Inserts all distinct alphabetical characters into variables set
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

    std::string toString() const;

    // /**
    //  * @return A 2D vector representing the truth table for the
    //  * AST stored in root. The last column represents a boolean
    //  * value for each combination of true/false values for variables
    //  * given in preceding columns. Top row has all variables set to
    //  * false and increases as binary does until all variables are 
    //  * set to true in the bottom row.
    //  */
    // std::vector<std::vector<bool>> generateTruthTable() const;

private:
    Node* root; // Root of the Abstract Syntax Tree
    // std::set<char> variables; // Ordered set of the variables in the AST in alphabetical order

    /**
     * Copies the parameter other quadtree into the current booleanExpression.
     * Called by copy constructor and operator=.
     * @param other The booleanExpression to be copied.
     */
    void copy(const booleanExpression& other);

    /**
     * Helper method for copy. Recursively copies
     * all of other data into new booleanExpression
     * @param other Node to copy.
     * @param parent parent of the Node to copy
     * @return Copied Node
     **/
    Node* copyNode(const Node* other, Node* parent);

    /**
     * Helper method for destructor
     */
    void clear();
};


#endif