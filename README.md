# ArithmeticExpr-Parser

## Introduction
Parsers are systems which read, analyze & evaluate input data conforming to some formal grammar [wikipedia link](https://en.wikipedia.org/wiki/Parsing). Below I present an Arithmetic Expression parser which evaluates an expression comprising of symbols \[ +  -  *  /  (  ) and numbers \]

## Description
The order of operations performed to evaluate an arithmetic expression is usually referred to by acronym of **BODMAS**(Bracket, Order, Division, Multiplication, Addition, Subtraction) or **PEMDAS**(Paranthesis, Exponents, Multiplication, Division, Addition, Subraction). Here we implement this order by formalizing it into a grammar. Grammars are the classical solution to parsing, as they formally define the structure of the input. Formal grammars are a much more detailed topic and for those interested further pls refer to this wikipedia page [Formal Grammars](https://en.wikipedia.org/wiki/Formal_grammar)

ArithmeticExpr-Parser consists of 2 sub-systems:-
1. Tokenizer
2. Evaluator

#### Tokenizer
In order to parse any input expression, we need to breakdown the input into its basic symbols/tokens. In our case the basic tokens of arithmetic expressions are the usual symbols \[ +  -  *  /  (  ) and numbers \]. For differentiating between - and -sign we follow the below rules

 * '-' can be an operator or a qualifier -ve numbers
 * '+' sign is not allowed as a qualifer(its always implicit)
 * successive signs are not allowed Ex:- 2--3, 2+-3 are invalid exprs. Use paranthesis to separate them like 2-(-3), 2+(-3)
 * if '-' is preceded by '*' or '/' or '(' or '' its a qualifier
 * otherwise '-' is an operator

#### Evaluator
Once tokens are available, the evaluator should follow the order of operations(**BODMAS**) to evaluate the tokens into the final result. We formalize **BODMAS** order into the below grammar.

 Grammar for evaluating arithmetic expressions:-
 ```
 * Expression:
 *       term //should end with a term
 *       Expression : + : term
 *       Expression : - : term    
 * term:
 *       primary //should end with a primary
 *       term : * : primary
 *       term : / : primary
 * primary:  
 *       float 
 *       ( expression ) 
 * 
 ```
The above grammar should be interpreted like this:-
1. **Expression** is a 
   - term OR
   - expression '+' term OR
   - expression '-' term
2. **term** is a
   - primary OR
   - term '*' primary OR
   - term '/' primary 
3. **primary** is a 
   - number(floating point) OR
   - expression enclosed in paranthesis

The above structure is naturally recursive and hence we can define functions for each of **expression**, **term** & **primary**. Another advantage of defining the order into a grammar is it is highly intuitive. 

The reasoning behind the grammar definition is :-

1. The order of evaluation of an expression is left to right(as + & - have same priority). Hence expression is defined as beginning with itself.
2. An expression consisting of ( * & / ) operators has higher-evaluation priority than expression, hence we define a separate unit called term. A term is also evaluated from left to right(as * & / have same priority), hence term starts with itself.
3. Any expression enclosed in paranthesis has higher-evaluation priority than term, hence we defined a separate unit called primary for ( expression ) and numbers. This is the base case.

An example evaluation order is shown below for a sample expression.

Input expression:- **2.3 + 3*(1+3)**

Its evaluation is broken into the below steps:-

- 2.3 + 3 * (1+3) : Rule 2 of expression: expression + term
  - 2.3 : Rule 1 of expression: term
    - 2.3 : Rule 1 of term : primary
      - 2.3 : Rule 1 of primary : number (**call returns**)
  - 3 * (1+3) : Rule 2 of term: term * primary
    - 3 : Rule 1 of term: primary
      - 3 : Rule 1 of primary: number (**call returns**)
    - (1+3) : Rule 2 of primary : expression enclosed in paranthesis
      - 1+3 : Rule 2 of expression : expression + term
        - 1 : Rule 1 of expression : term
          - 1 : Rule 1 of term : primary
            - 1 : Rule 1 of primary : number (**call returns**)
        - 3 : Rule 1 of term : primary
          - 3 : Rule 1 of primary : number (**call returns**)

          
                  

