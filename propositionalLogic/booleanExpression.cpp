#include "booleanExpression.h"
#include <map>

booleanExpression::booleanExpression(std::string &expression) {
    Parser parser(expression);
    root = parser.parse();
    
    table = new TruthTable(root);
}


booleanExpression::booleanExpression(const booleanExpression& other) {
    copy(other);
}

void booleanExpression::copy(const booleanExpression& other) {
    root = copyNode(other.root, nullptr);
    table = other.table;
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
    clear();
}

void booleanExpression::clear() {
    delete table;
    delete root;
}


booleanExpression& booleanExpression::operator=(const booleanExpression& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

bool booleanExpression::evaluate(const std::map<char, bool>& vars) const{
    return root->evaluate(vars);
}

std::string booleanExpression::toString() const {
    return root->toString();
}
