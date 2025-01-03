#include "TruthTable.h"


TruthTable::TruthTable(Node* &node) : root(node) {
    generateTruthTable();
}

void TruthTable::generateTruthTable() {
    std::set<char> variables = findVariables();
    int numOfVars = variables.size();
    int numOfRows = std::pow(2, numOfVars);
    

    std::vector<std::vector<bool>> table(numOfRows, std::vector<bool>(numOfVars + 1));

    for (int row = 0; row < numOfRows; ++row) {
        std::map<char, bool> vars;
        int col = 0;
        
        for (char var : variables) {
            table[row][col] = (row >> (numOfVars - col - 1)) & 1;

            vars[var] = table[row][col];
            col++;
        }
        table[row][col] = root->evaluate(vars);
    }
    this->table = table;
}

std::set<char> TruthTable::findVariables() {
    std::set<char> variables;
    findVariablesHelper(root, variables);
    return variables;
}

void TruthTable::findVariablesHelper(Node* &currNode, std::set<char> &variables) {
    if (!currNode) return;
    
    if (currNode->type == VAR) variables.insert(currNode->value[0]);

    findVariablesHelper(currNode->left, variables);
    findVariablesHelper(currNode->right, variables);
}



