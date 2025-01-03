
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

Node::~Node() {
    delete left;
    delete right;
}

bool Node::operator==(const Node& rhs) {
    if (value != rhs.value) return false;
    if (left != rhs.left) return false;
    if (right != rhs.right) return false;
    return true;
}


void Node::print() const {
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


bool Node::evaluateVariable(const std::map<char, bool>& vars) const {
    assert(vars.contains(value[0]) && 
            "Variable not in given map");
    return vars.at(value[0]);
}

bool Node::evaluateOperator(const std::map<char, bool>& vars) const {
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
        default: throw InvalidSymbolException("Invalid symbol detected");
    }
}

bool Node::evaluate(const std::map<char, bool>& vars) const {
    if (type == VAR) return evaluateVariable(vars);
    return evaluateOperator(vars);
}