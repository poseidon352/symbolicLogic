#include "Parser.h"
#include "stack"
#include <cassert>
#include <iostream>

// Constructor
Parser::Parser(const string& expr) : expr(removeAllWhitespace(expr)) {}

string Parser::removeAllWhitespace(const string& str) {
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

bool Parser::hasLeftAssociativity(string &op) {
    return op == "&" || op == "|" || op == "<->";
}

int Parser::getPrecedence(string &op) {
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

queue<string> Parser::infixToRpn() {
    // expression in Reverse Polish Notation format
    queue<string> rpn;
    // operator stack for parsing expression (VAR type is used to represent a left parenthesis)
    stack<string> opStack;

    // Implementation of the Shunting Yard Algorithm
    for (int i = 0; i < expr.length(); i++) {
        if (isalpha(expr[i])) {
            // If the string is a letter (a variable) then at it to the rpn queue
            rpn.push(string(1, expr[i]));
        } else if (expr[i] == '(') {
            opStack.push(string(1, expr[i]));
        } else if (expr[i] == ')') {
            while (opStack.top() != "(") {
                assert(!opStack.empty() && "Mismatched parentheses found");
                // pop operators from opStack into output queue
                rpn.push(opStack.top());
                opStack.pop();
            }
            // There should now be a left parenthesis at the top of the opStack
            assert(opStack.top() == "(" && "Mismatched parentheses found");
            // Pop the left parenthesis from the opStack and discard it
            opStack.pop();
        } else {
            int opSize = operatorSize(i);
            string op = expr.substr(i, opSize);
            int precedence = getPrecedence(op);

            while (!opStack.empty() && opStack.top() != "(" && 
            ((getPrecedence(opStack.top()) >= precedence) || 
            (getPrecedence(opStack.top()) == precedence && hasLeftAssociativity(op)))) {
                // pop operators from opStack into output queue
                rpn.push(opStack.top());
                opStack.pop();
            }
            opStack.push(op);
            // Increment the index as to not read longer operators twice
            i += opSize - 1;
        }
    }

    while (!opStack.empty()) {
        assert(opStack.top() != "(" && "Mismatched parentheses found");
        rpn.push(opStack.top());
        opStack.pop();
    }

    return rpn;
}

Node* Parser::rpnToExpr(queue<string> &queue) {
    stack<Node*> stack;
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
            // If the operator is NOT then leave the lhs as a nullptr
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
    Node* result = stack.top();
    stack.pop();
    return result;
}

// Public parse function
Node* Parser::parse() {

    queue<string> rpn = infixToRpn();

    return rpnToExpr(rpn);
}