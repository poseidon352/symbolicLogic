#include "Parser.h"
#include "stack"
#include <cassert>
#include <iostream>

Parser::Parser(const std::string& expr) : expr(removeAllWhitespace(expr)) {}

std::string Parser::removeAllWhitespace(const std::string& str) {
    std::string result;
    std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                 [](unsigned char c) { return !std::isspace(c); });
    return result;
}


int Parser::operatorSize(int index) {
    if (expr[index] == '~' || expr[index] == '&' || expr[index] == '|') {
        return 1;
    } else if (expr[index] == '-' && index < expr.length() - 1 && expr[index + 1] == '>') {
        return 2;
    } else if (expr[index] == '<' && index < expr.length() - 2 && expr[index + 1] == '-' && expr[index + 2] == '>') {
        return 3;
    }
    return -1;
}

bool Parser::hasLeftAssociativity(std::string &op) {
    return op == "&" || op == "|" || op == "<->";
}

int Parser::getPrecedence(std::string &op) {
    if (op == "|") {
        return 1;
    } else if (op == "&") {
        return 2;
    } else if (op == "->") {
        return 3;
    } else if (op == "<->") {
        return 4;
    } else if (op == "~") {
        return 5;
    } else {
        return -1;
    }
}

/**
 * @todo Fix incorrect parsing, ex. C & ~~D parses as ~C & ~D. 
 * Also ~~D segfaults.
 */
std::queue<std::string> Parser::infixToRpn() {
    assert((operatorSize(0) == -1 || expr[0] == '~') && 
        "Invalid Syntax (invalid operator at start of expression)");

    assert((isalpha(expr[expr.length() - 1]) || expr[expr.length() - 1] == ')') && 
        "Invalid Syntax (operator at end of expression)");

    // Expression in Reverse Polish Notation format
    std::queue<std::string> rpn;
    // Operator stack for parsing expression
    std::stack<std::string> opStack;

    // Implementation of the Shunting Yard Algorithm
    for (int i = 0; i < expr.length(); i++) {
        if (isalpha(expr[i])) {
            // If the char is a letter (a variable) then it is enqued to rpn
            rpn.push(std::string(1, expr[i]));
        } else if (expr[i] == '(') {
            opStack.push(std::string(1, expr[i]));
        } else if (expr[i] == ')') {
            while (opStack.top() != "(") {
                assert(!opStack.empty() && "Mismatched parentheses found");
                // Pop operators from opStack into rpn queue
                rpn.push(opStack.top());
                opStack.pop();
            }
            // There should now be a left parenthesis at the top of the opStack
            assert(opStack.top() == "(" && "Mismatched parentheses found");
            // Pop the left parenthesis from the opStack and discard it
            opStack.pop();
        } else {
            int opSize = operatorSize(i);
            auto op = expr.substr(i, opSize);
            int precedence = getPrecedence(op);

            while (!opStack.empty() && opStack.top() != "(" && 
            ((getPrecedence(opStack.top()) >= precedence) || 
            (getPrecedence(opStack.top()) == precedence && hasLeftAssociativity(op)))) {
                // Pop operators from opStack into output queue
                rpn.push(opStack.top());
                opStack.pop();
            }
            opStack.push(op);
            // Increment the index as to not read longer operators twice
            i += opSize - 1;
            if (i < expr.length() - 1)
                assert((operatorSize(i + 1) == -1 || expr[i + 1] == '~') &&
                        "Invalid Syntax (invalid operators adjacent)");
        }
    }
    // Pop the rest of the operators from opStack into rpn queue
    while (!opStack.empty()) {
        assert(opStack.top() != "(" && "Mismatched parentheses found");
        rpn.push(opStack.top());
        opStack.pop();
    }

    return rpn;
}

Node* Parser::rpnToExpr(std::queue<std::string> &queue) {
    std::stack<Node*> stack;
    while (!queue.empty()) {
        if (queue.front().length() == 1 && isalpha(queue.front()[0])) {
            // If the front of the queue is a letter (so a VAR) then push it onto the stack
            stack.push(new Node(queue.front()));
        } else {
            // Otherwise it is an operator
            // The top two elements on the stack are the left and right hand side of the operator
            Node* op = new Node(queue.front());
            Node* rhs = stack.top();
            stack.pop();
            rhs->parent = op;
            op->right = rhs;
            // If the operator is NOT then leave lhs as nullptr
            if (op->type != NOT) {
                Node* lhs = stack.top();
                stack.pop();
                lhs->parent = op;
                op->left = lhs;
            }
            stack.push(op);
        }
        queue.pop();
    }
    auto result = stack.top();
    stack.pop();
    return result;
}

Node* Parser::parse() {

    auto rpn = infixToRpn();

    return rpnToExpr(rpn);
}