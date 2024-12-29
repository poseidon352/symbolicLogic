#ifndef NODE_H
#define NODE_H

#include <string>
#include <unordered_map>
using namespace std;

// Enum for Boolean operators
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
    Type type; 
    string value;
    Node* parent;
    Node* left;                          // Left child (nullptr for variables)
    Node* right;                         // Right child (nullptr for variables or NOT)

    // Constructors
    Node(const string& var);
    Node(const string& var, Node* lhs, Node* rhs);

    void print();
};

#endif