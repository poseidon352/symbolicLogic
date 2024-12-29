
#include "Parser.h"
#include "Node.h"
#include <iostream>

int main() {
    std::string expression = "~(A & B) | C";
    
    // Parse the expression into an AST
    Parser parser(expression);
    Node* root = parser.parse();
    
    // Print the AST
    std::cout << "AST for expression: " << expression << std::endl;
    root->print();
    std::cout << endl;
    return 0;
}