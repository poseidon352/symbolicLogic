#include "booleanExpression.h"
#include <iostream>

int main() {
    std::string expression = "(A & B & ~C) | (~A & ~B & C)";
    
    booleanExpression expr = booleanExpression(expression);
    std::cout << expr.toString() << std::endl;
    std::cout << expr.table->toString() << std::endl;
    return 0;
}