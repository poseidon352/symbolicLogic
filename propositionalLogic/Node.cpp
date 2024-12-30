
#include <exception>
#include <iostream>
#include "Node.h"

class InvalidSymbolException : public std::exception {
private:
    std::string message;

public:
    InvalidSymbolException(const char* msg) : message(msg) {}

    const char* what() const throw() {
        return message.c_str();
    }
};

Node::Node(const std::string& var): value(var), parent(nullptr), left(nullptr), right(nullptr) {
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

Node::Node(const std::string& var, Node* parent, Node* lhs, Node* rhs): value(var), parent(parent), left(lhs), right(rhs) {
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
    // Parentheses are not added if Node has NOT or VAR type or has
    // no parent (is the root of the Abstract Syntax Tree)
    bool addParens = (type != NOT && type != VAR) && parent;
    // Print opening parenthesis if needed
    if (addParens) std::cout << "(";

    if (left) {
        left->print();
        std::cout << " ";
    }
    std::cout << value;
    if (right) {
        // Spacing not added for NOT type for easier readability
        if (type != NOT) std::cout << " ";
        right->print();
    }
    // Print closing parenthesis if needed
    if (addParens) std::cout << ")";
}

