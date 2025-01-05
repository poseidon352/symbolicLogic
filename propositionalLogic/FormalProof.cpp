#include "FormalProof.h"
#include <cassert>
#include <stdexcept>
#include <iostream>

FormalProof::FormalProof(Node* root): root(root) {
    setPremiseConclusion();
    prove(root);
}

void FormalProof::setPremiseConclusion() {
    assert(root && "root has not has not been initialized");

    switch (root->type) {
        case VAR: premise, conclusion = root;
                  break;
        case CON: premise = root->left;
                  conclusion = root->right;
                  break;
        case BICON: // TODO
                  break;
        default: throw std::runtime_error("Incorrect root Type");
    }
}

void FormalProof::prove(Node* currNode) {
    if (root->type == CON) {
        conditionalProof(currNode);
    }

}

void FormalProof::conditionalProof(Node* currNode) {
    Node* lhs = currNode->left;
    Node* rhs = currNode->right;

    assumptions.push_back(lhs);
    steps.push_back(new Step(lhs, ASSUMPTION, 0));
    toProve.push(rhs);
    if (lhs->type == VAR && rhs->type == OR) {
        lhsVarRhsOr(currNode);
    }
}

void FormalProof::lhsVarRhsOr(Node* currNode) {
    Node* varNode = currNode->left;
    Node* orNode = currNode->right;

    Step* newStep;
    if (varNode == orNode->left) {
        newStep = new Step(orNode, ORintro, 1);
    }

    steps.push_back(newStep);
    if (newStep->expression == toProve.front()) {
        toProve.pop();
    }

    // TODO: Deal with condition that neither are true
}