#include <ArithExprParser.h>

/* Tokenize
 * create 3 kinds of tokens: 
 *          1) numbers -ve or +ve
 *          2) operators +,-,*,/
 *          3) paranthesis ( )
 * 
 * ------------------------------
 * Rules for treating '-'
 * ------------------------------
 * '-' can be both an operator or to qualify -ve numbers
 * '+' sign is not allowed as qualifer(its always implicit)
 * successive signs are not allowed Ex:- 2--3, 2+-3 are invalid exprs. Use paranthesis to separate them like 2-(-3), 2+(-3)
 * -2*-4+(-2*3) is valid expr
 * qualifier '-' is preceded by '*' or '/' or '(' or ''
 * otherwise '-' is operator
 */
std::vector<token> ArithExprParser::tokenize(std::string& expr){
    
    std::string c;
    token prev_token = {TYPES::NUM,""};
    tokens.clear();
    int start,i = 0;
    while(i < expr.size()){
        c = expr.substr(i,1);
        if(c == "(" or c == ")"){
            tokens.push_back(token{TYPES::PAR,c});
            i++;
        }
        else if(c == "-"){
                if(prev_token.value == "" or prev_token.value == "(" or 
                   prev_token.value == "*" or prev_token.value == "/"){
                    start = ++i;
                    while(i < expr.size() and (isdigit(expr[i]) or expr[i] == '.'))
                        i++;
                    if(start < expr.size())
                        tokens.push_back(token{TYPES::NUM, '-' + expr.substr(start, i-start)});
                    else
                        throw invalidexpr;
                }else{
                    tokens.push_back(token{TYPES::OPR,c});
                    i++;
                }
        }else if(c == "+" or c == "*" or c == "/" or c == "%"){
            tokens.push_back(token{TYPES::OPR,c});
            i++;
        }
        else if(isdigit(expr[i])){
             start = i;
             while(i < expr.size() and (isdigit(expr[i]) or expr[i] == '.'))
                i++;
             tokens.push_back(token{TYPES::NUM, expr.substr(start, i-start)});
        }
        else{
            throw invalidexpr;
            break;
        }
        prev_token = tokens.back(); 
    }
    return tokens;
}


//evaluate numbers & ( expression )
double ArithExprParser::primary(int& end){
    /* primary:
     *      float
     *      (expression)
     */ 
     double p;
     if(tokens[end].value == ")"){
        p = expression(--end);
        if(end >= 0 and tokens[end--].value == "("){
            return p;
        }
        else
            throw invalidexpr;
    }else if(end >= 0 and tokens[end].type == TYPES::NUM){
        p = std::stof(tokens[end--].value);
        return p;
    }else
        throw invalidexpr;
}

//evaluate terms
double ArithExprParser::term(int& end){
   /*
    * term:
    *       primary //end with primary
    *       term : * : primary
    *       term : / : primary
    *   
    */ 
        //should end with a primary
        double t = primary(end);
        if(end >= 0 and tokens[end].value == "*")
            return term(--end) * t;
        else if(end >= 0 and tokens[end].value == "/")
            return term(--end) / t;
        else
            return t;
}

//evaluate expression
double ArithExprParser::expression(int& end){
/*
 * Expression:
 *       term //end with a term
 *       Expression : + : term
 *       Expression : - : term
 */ 
 
     double t = term(end);
     if(end >= 0){
         if(tokens[end].type == TYPES::OPR){
             if(tokens[end].value == "+")
                 return expression(--end) + t;
             else if(tokens[end].value == "-")
                 return expression(--end) - t;
             else
                 throw invalidexpr;
         }
     }
     
     return t;
     
}


double ArithExprParser::evaluate(){
    int end = tokens.size()-1;
    return expression(end);
}