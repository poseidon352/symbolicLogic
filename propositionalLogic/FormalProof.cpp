#include "FormalProof.h"

FormalProof::FormalProof(Node* root): root(root) {}

void FormalProof::prove(Node* currNode, std::string proof) {
    if (root->left == root->right) return;

}
