#include <iostream>
#include <ArithExprParser.h>

int main()
{
    std::string expr;
    ArithExprParser parser;
    while(true){
        std::cout<<"Enter Expression or type 'Q' to quit:";
        std::cin>>expr;
        if(expr == "Q")
            break;
        parser.tokenize(expr);
        std::cout<<"Result = "<<parser.evaluate();
    }
    
}
