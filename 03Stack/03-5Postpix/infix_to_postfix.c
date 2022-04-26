#include "linkedstack.h"

int isOperator(char c)
{
	char *s = "()*/+-";
	while (*s)
	{
		if (*s == c)
			return (TRUE);
		s++;
	}
	return (FALSE);
}

int checkPriority(char c, int data)
{
	int priority1;
	int priority2;

	switch (c)
	{
		case '*':
		case '/':
			priority1 = 2;
			break;
		case '+':
		case '-':
			priority1 = 1;
			break;
		case '(':
			priority1 =0;
	}
	switch (data)
	{
		case '*':
		case '/':
			priority2 = 2;
			break;
		case '+':
		case '-':
			priority2 = 1;
			break;
		case '(':
			priority2 =0;
	}
	return (priority1 - priority2);
}

void	infixToPostfix(char *expr)
{
	LinkedStack *stack;
	StackNode	*popedNode;
	StackNode	element;

	stack = createLinkedStack();

	while (*expr)
	{
		if (!isOperator(*expr))
			printf("%c", *expr);
		else if (*expr == ')')
		{
			while ((popedNode = peek(stack))->data != '(')
			{
				StackNode *popedOper = pop(stack);
				printf("%c", popedOper->data);
				free(popedOper);
			}
			free(popedNode = pop(stack));
		}
		else if (*expr == '(')
		{
			element.data = *expr;
			push(stack, element);
		}
		else
		{
			if (!isLinkedStackEmpty(stack))
			{
				while (!isLinkedStackEmpty(stack) && 
						checkPriority(*expr, (popedNode = peek(stack))->data) <= 0 && 
						popedNode->data != '(')
						{
							StackNode *popedOper = pop(stack);
							printf("%c",popedOper->data);
							free(popedOper);
						}
			}
			element.data = *expr;
			push(stack, element);
		}
		expr++;
	}
	while (stack->currentElementCount)
	{
		popedNode = pop(stack);
		printf("%c", popedNode->data);
		free(popedNode);
	}
	printf("\n");
	deleteLinkedStack(stack);
}

int main(void)
{
	char *exp = "2-(5+3)*10";

	printf("%s \n",exp);
	infixToPostfix(exp);
	system("leaks a.out > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
}