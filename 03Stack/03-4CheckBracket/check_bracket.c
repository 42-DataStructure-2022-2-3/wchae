#include "linkedstack.h"
/*
( ( A * B ) / C ) - { ( D + E ) && ( F – G ) } 

( ( A * B ) / C - { ( D + E ) && ( F – G ) ) }

*/

static int  is_open_bracket(int c)
{
    if (c == '(' || c == '[' || c == '{')
        return (TRUE);
    return (FALSE);
}

static int  is_close_bracket(int c)
{
    if (c == ')' || c == ']' || c == '}')
        return (TRUE);
    return (FALSE);
}

int checkBracketMatching(char *exp)
{
    LinkedStack *stack = createLinkedStack();
    StackNode   node;
    StackNode   *poped;
    int flag;
    int c;

    while (*exp)
    {
        if (is_open_bracket(*exp))
        {
            node.data = *exp;
            push(stack, node);
        }
        else if (is_close_bracket(*exp))
        {
            poped = pop(stack);
            c = poped->data;
			free(poped);
			deleteLinkedStack(stack);
            if(!c)
                return (FALSE);
            else
            {
                if (c == '(' && *exp != ')')
                    return (FALSE);
                if (c == '{' && *exp != '}')
                    return (FALSE);
                if (c == '[' && *exp != ']')
                    return (FALSE);
            }
        }
        exp++;
    }
    return (TRUE);
}

int main(void)
{
    char    *expression = "(( 20 * 30 ) / 10) - { ( D + E ) && ( F - G) } ";
    char    *wrong = "(( 20 * 30 ) / 10 - { ( D + E ) && ( F - G)) } ";

    printf("OK = %d\n", checkBracketMatching(expression));
    printf("X = %d\n", checkBracketMatching(wrong));
    system("leaks a.out");
}