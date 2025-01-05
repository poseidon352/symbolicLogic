#ifndef _FORMALPROOF_H_
#define _FORMALPROOF_H_

#include "Node.h"
#include <queue>

enum Rule {
    NOTintro,
    ANDintro,
    ORintro,
    CONintro,
    BICONintro,
    CONTRADICTIONintro,
    NOTelim,
    ANDelim,
    ORelim,
    CONelim,
    BICONelim,
    CONTRADICTIONelim,
    ASSUMPTION,
    CONCLUSION
};

class FormalProof {
public:
    FormalProof(Node* root);

    void prove(Node* currNode);

private:
    class Step {
    public:
        Node* expression;
        Rule rule;
        int depth;

        Step(Node* expression, Rule rule, int depth);
    
    };

   Node* root;
   Node* premise;
   Node* conclusion;
   std::vector<Step*> steps;
   std::vector<Node*> assumptions;
   std::queue<Node*> toProve;

   void setPremiseConclusion();

   void conditionalProof(Node* currNode);

   void lhsVarRhsOr(Node* currNode);

   bool satisfiesRule(Rule rule, std::vector<Step*> procedure);
};
#endif