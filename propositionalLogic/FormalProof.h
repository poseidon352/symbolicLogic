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
        std::vector<int> supportingSteps;
        int depth;

        Step(Node* expression, Rule rule, std::vector<int> supportingSteps, int depth);
    
    };

   /**
    * @note First Assumption will have depth 0, following steps will have depth 1 when
    * contained by that assumption.
    */

   Node* root;
   Node* premise;
   Node* conclusion;
   std::vector<Step*> steps;
   std::vector<Node*> assumptions;
   std::queue<Node*> toProve;

   void setPremiseConclusion();

   void conditionalProof(Node* currNode);

   void lhsVarRhsOr(Node* currNode);

   bool satisfiesRule(const std::vector<Step*> procedure, const Step* lastStep) const;

   bool checkNOTintro(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkANDintro(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkORintro(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkCONintro(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkCONTRADICTIONintro(const std::vector<Step*> procedure, const Step* lastStep) const;
};
#endif