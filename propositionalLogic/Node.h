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
    VAR
};

class Node {
public:
    Type type;                           // Propositional logic type
    std::string value;                   // String representation of Node
    Node* parent;                        // Ancestor (nullptr for root of AST)
    Node* left;                          // Left child (nullptr for VAR, NOT)
    Node* right;                         // Right child (nullptr for VAR)

    // Node Constructor
    Node(const std::string& var);
    
    // Node destructor
    ~Node();

    // // Node copy constructor
    Node(const Node& other);

    // Node assignment operator
    Node& operator=(const Node& rhs);

    bool operator==(const Node& rhs);

    /**
     * Print the value stored in this node and all of its children,
     * adding parentheses and spacing when need for clarity and correctness.
     */
    std::string toString() const;

    /**
     * @todo Add documentation for evaluate methods
     */
    bool evaluate(const std::map<char, bool>& vars) const;

private:
    bool evaluateVariable(const std::map<char, bool>& vars) const;
    bool evaluateOperator(const std::map<char, bool>& vars) const;

};

#endif