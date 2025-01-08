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
    ASSUMPTION
};

class FormalProof {
public:
    FormalProof(Node* root);
    FormalProof(Node* root, int depth);

    void prove();

private:
    class Step {
    public:
        Node* expression;
        Rule rule;
        int depth;

        Step(Node* expression, Rule rule, int depth);
    
    };

   /**
    * @note First Assumption will have depth 0, following steps will have depth 1 when
    * contained by that assumption.
    */

   Node* root;
   Node* premise;
   Node* conclusion;
   int depth;
   std::vector<Step*> steps;
   std::vector<Step*> assumptions;
   std::queue<Node*> toProve;

   void setPremiseConclusion();

   void conditionalProof();

   void proveOR();

   bool satisfiesRule(const std::vector<Step*> procedure, const Step* lastStep) const;

   bool checkNOTintro(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkANDintro(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkORintro(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkCONintro(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkCONTRADICTIONintro(const std::vector<Step*> procedure, const Step* lastStep) const;

   bool checkNOTelim(const std::vector<Step*> procedure, const Step* lastStep) const;
   bool checkANDelim(const std::vector<Step*> procedure, const Step* lastStep) const;
};
#endif