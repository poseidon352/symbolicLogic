#include "booleanExpression.h"
#include <iostream>

int main() {
    std::string expression;
    std::cout << "Enter your expression here: ";
    std::getline(std::cin, expression);
    
    booleanExpression expr = booleanExpression(expression);
    std::cout << expr.toString() << std::endl;
    std::cout << expr.table->toString() << std::endl;
    return 0;
}