#include "linkedstack.h"
#include "exprdef.h"

int pushLSExprToken(LinkedStack *stack, ExprToken data)
{
    StackNode node;
    node.data = data.value;
    return push(stack, node);
}

void calcExpr(ExprToken *pExprTokens, int tokenCount)
{
    LinkedStack *stack;
    StackNode   *node1;
    StackNode   *node2;
    Precedence tokenType;
    int i = 0;

    if (!pExprTokens)
        return;

    stack = createLinkedStack();
    
    for (int i = 0; i < tokenCount; i++)
    {
        tokenType = pExprTokens[i].type;
        if (tokenType == operand)
            pushLSExprToken(stack, pExprTokens[i]);
        else
        {
            node2 = pop(stack);
            if (node2)
            {
                node1 = pop(stack);
                if (node1)
                {
                    float op1 = node1->data.=
                }
            }
        }
    }
}
