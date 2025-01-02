
#include "booleanExpression.h"
#include <iostream>

int main() {
    std::string expression = "(A & (C | D))";
    
    booleanExpression expr = booleanExpression(expression);
    expr.printExpression();

    std::vector<std::vector<bool>> table = expr.generateTruthTable();
    for (const auto& row : table) {
        for (bool bit : row) {
            std::cout << bit << " ";
        }
        std::cout << "\n";
    }
    return 0;
}