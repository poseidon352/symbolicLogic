#ifndef NODE_H
#define NODE_H

#include <string>
#include <unordered_map>
#include <map>

// Enum for propositional logic types
enum Type {
    NOT,
    AND,
    OR,
    CON,
    BICON,
    VAR,
    TRUE,
    FALSE
};

class Node {
public:
    Type type;                           // Propositional logic type
    std::string value;                   // String representation of Node
    Node* parent;                        // Ancestor (nullptr for root of AST)
    Node* left;                          // Left child (nullptr for VAR, NOT, TRUE and FALSE)
    Node* right;                         // Right child (nullptr for VAR, TRUE and FALSE)

    // Constructors
    Node(const std::string& var);
    Node(const std::string& var, Node* parent, Node* lhs, Node* rhs);

    /**
     * Print the value stored in this node and all of its children,
     * adding parentheses and spacing when need for clarity and correctness.
     */
    void print();

    bool evaluate(std::map<char, bool> vars);

private:
    bool evaluateVariable(std::map<char, bool> vars);
    bool evaluateOperator(std::map<char, bool> vars);
};

#endif