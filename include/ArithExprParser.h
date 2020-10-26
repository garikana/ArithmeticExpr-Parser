#pragma once
#include <vector>
#include <string>
#include <exception>

/* 
 * Grammar for evaluating arithmetic expressions
 * Expression:
 *       term //should end with a term
 *       Expression : + : term
 *       Expression : - : term
 *       
 * term:
 *       primary //should end with a primary
 *       term : * : primary
 *       term : / : primary
 * 
 * primary:
 *      
 *       float 
 *       ( expression ) 
 * 
 *
 */

enum TYPES{ NUM = 0, OPR, PAR };

//exception class
class myexception: public std::exception{
    const char* what() const throw()
    {
        return "Invalid Expression";
    }
};

//token 
struct token{
    TYPES type; //token type
    std::string value; //token value
}; 

class ArithExprParser{
public:
    ArithExprParser()=default;
    std::vector<token> tokenize(std::string& expr);
    double evaluate();
    
private:
    std::vector<token> tokens;
    myexception invalidexpr;
    double expression(int& end);
    double term(int& end);
    double primary(int& end);
};