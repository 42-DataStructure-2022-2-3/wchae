#ifndef _EXPR_DEF_
# define _EXPR_DEF

typedef enum PrecedenceType { 
    lparen, 
    rparen, 
    times, 
    divide, 
    plus, 
    minus, 
    //피연산자
    operand 
} Precedence;
typedef struct ExprTokenType {
    float value;
    Precedence type;
} ExprToken;

#endif