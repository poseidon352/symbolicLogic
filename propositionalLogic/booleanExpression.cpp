#include "booleanExpression.h"
#include <bitset>
#include <algorithm>
#include <iostream>
#include <map>

booleanExpression::booleanExpression(std::string &expression) {
    Parser parser(expression);
    root = parser.parse();
}


booleanExpression::booleanExpression(const booleanExpression& other) {
    copy(other);
}

void booleanExpression::copy(const booleanExpression& other) {
    root = copyNode(other.root, nullptr);
}

Node* booleanExpression::copyNode(const Node* node, Node* parent) {
        if (!node) return nullptr;

        Node* newNode = new Node(node->value);

        newNode->parent = parent;

        newNode->left = copyNode(node->left, newNode);
        newNode->right = copyNode(node->right, newNode);

        return newNode;
}


booleanExpression::~booleanExpression() {
    delete root;
}


booleanExpression& booleanExpression::operator=(const booleanExpression& rhs) {
    if (this != &rhs) {
        delete root;
        copy(rhs);
    }
    return *this;
}

bool booleanExpression::evaluate(const std::map<char, bool>& vars) const{
    return root->evaluate(vars);
}

void booleanExpression::printExpression() {
    root->print();
    std::cout << std::endl;
}

// /** @todo Maybe only have the variables be computed in a method
//  * called here, since it is only used in this method. */ 
// std::vector<std::vector<bool>> booleanExpression::generateTruthTable() const {
//     int numOfVars = variables.size();
//     int numOfRows = std::pow(2, numOfVars);
    

//     std::vector<std::vector<bool>> table(numOfRows, std::vector<bool>(numOfVars + 1));

//     for (int row = 0; row < numOfRows; ++row) {
//         std::map<char, bool> vars;
//         int col = 0;

//         for (char var : variables) {
//             table[row][col] = (row >> (numOfVars - col - 1)) & 1;

//             vars[var] = table[row][col];
//             col++;
//         }
//         table[row][col] = root->evaluate(vars);
//     }
    
//     return table;
// }