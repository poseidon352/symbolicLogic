#ifndef _FORMALPROOF_H_
#define _FORMALPROOF_H_

#include "Node.h"

enum Rule {
    NOTI,
    ANDI,
    ORI,
    CONI,
    BICONI,
    NOTE,
    ANDE,
    ORE,
    CONE,
    BICONE,
    FALSE
};

class FormalProof {
public:
    FormalProof(Node* root);

    void prove(Node* currNode, std::string proof);

private:
   Node* root;

};
#endif