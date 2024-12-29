
#include <exception>
#include <iostream>
#include "Node.h"
using namespace std;

class InvalidSymbolException : public exception {
private:
    string message;

public:
    InvalidSymbolException(const char* msg) : message(msg) {}

    const char* what() const throw() {
        return message.c_str();
    }
};

Node::Node(const string& var): value(var), parent(nullptr), left(nullptr), right(nullptr) {
    if (var == "~") {
        type = NOT;
    } else if (var == "&") {
        type = AND;
    } else if (var == "|") {
        type = OR;
    } else if (var == "->") {
        type = CON;
    } else if (var == "<->") {
        type = BICON;
    } else if (var.length() == 1 && isalpha(var[0])) {
        type = VAR;
    } else {
        throw InvalidSymbolException("Invalid symbol detected");
    }
}

Node::Node(const string& var, Node* lhs, Node* rhs): value(var), left(lhs), right(rhs) {
    if (var == "~") {
        type = NOT;
    } else if (var == "&") {
        type = AND;
    } else if (var == "|") {
        type = OR;
    } else if (var == "->") {
        type = CON;
    } else if (var == "<->") {
        type = BICON;
    } else if (var.length() == 1 && isalpha(var[0])) {
        type = VAR;
    } else {
        throw InvalidSymbolException("Invalid symbol detected");
    }
}

void Node::print() {
    bool addParens = (type != NOT && type != VAR) && parent;
    // bool addParens = type != VAR && parent;
    // Print opening parenthesis if needed
    if (addParens) cout << "(";

    if (left) {
        left->print();
        cout << " ";
    }
    cout << value;
    if (right) {
        if (type != NOT) cout << " ";
        right->print();
    }
    // Print closing parenthesis if needed
    if (addParens) cout << ")";
}

