#ifndef _BOOLEANEXPRESSION_H_
#define _BOOLEANEXPRESSION_H_

#include "Node.h"
#include <set>

class TruthTable {
public:
    std::vector<std::vector<bool>> table;

    TruthTable(Node* &root);



private:
    Node* root;

    void generateTruthTable();

    std::set<char> findVariables();
    void findVariablesHelper(Node* &currNode, std::set<char> &variables);

};



#endif