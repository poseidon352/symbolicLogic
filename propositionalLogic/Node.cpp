
#include <exception>
#include <iostream>
#include <cassert>
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


bool Node::evaluateVariable(std::map<char, bool> vars) {
    assert(vars.contains(value[0]) && 
            "Variable not in hashmap");
    return vars.at(value[0]);
}

bool Node::evaluateOperator(std::map<char, bool> vars) {
    switch (type) {
        case NOT:
            return !right->evaluate(vars);
        case AND:
            return left->evaluate(vars) && right->evaluate(vars);
        case OR:
            return left->evaluate(vars) || right->evaluate(vars);
        case CON:
            return !left->evaluate(vars) || right->evaluate(vars);
        case BICON:
            return (!left->evaluate(vars) || right->evaluate(vars)) &&
                   (!right->evaluate(vars) || left->evaluate(vars));
        default: return false;
    }
}

bool Node::evaluate(std::map<char, bool> vars) {
    if (type == TRUE) return true;
    if (type == FALSE) return false;

    if (type == VAR) {
        return evaluateVariable(vars);
    }
    return evaluateOperator(vars);
}