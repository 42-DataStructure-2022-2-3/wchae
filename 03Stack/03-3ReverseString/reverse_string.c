#include <string.h>
#include "linkedstack.h"

char    *reverse_string(char    *str)
{
    char    *reversed;
    int     i;
    int     str_len;

    LinkedStack *stack;
    StackNode   node;

    if (!str)
        return NULL;
    str_len = strlen(str);
    reversed = (char *)malloc(sizeof(char) *str_len + 1);
    
    stack = createLinkedStack();
    for (int i = 0; i < str_len; i++)
    {
         node.data = str[i];
         push(stack, node);
    }
    for (int i = 0; i < str_len; i++)
    {
        StackNode *poped;
        poped = pop(stack);
        reversed[i] = poped->data;
        free(poped);
    }
    deleteLinkedStack(stack);
    return (reversed);
}

int main()
{
    char    *str = "ABCDEFG";
    char    *reversed;
    printf("original = %s\n", str);
    reversed = reverse_string(str);
    printf("reversed = %s\n", reversed);
    free(reversed);
    system("leaks a.out");
}