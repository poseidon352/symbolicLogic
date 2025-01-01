#include "booleanExpression.h"


// Constructor
booleanExpression::booleanExpression(std::string &expression) {
    Parser parser(expression);
    root = parser.parse();
}

// Copy constructor
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

// Destructor
booleanExpression::~booleanExpression() {
    clear(root);
}

void booleanExpression::clear(Node* &node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// assignment operator
booleanExpression& booleanExpression::operator=(const booleanExpression& rhs) {
    if (this != &rhs) {
        clear(root);
        copy(rhs);
    }
    return *this;
}

bool booleanExpression::evaluate(const std::map<char, bool>& vars) const{
    return root->evaluate(vars);
}