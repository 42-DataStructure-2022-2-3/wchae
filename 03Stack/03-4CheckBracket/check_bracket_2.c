#include "linkedstack.h"
int	matchSymbol(StackNode *checkSymbol, StackNode symbol)
{
	int	ret = FALSE;

	switch(symbol.data)
	{
		case ')':
			if (checkSymbol->data == '(')
				ret = TRUE;
				break;
		case '{':
			if (checkSymbol->data == '{')
				ret = TRUE;
				break;
		case '[':
			if (checkSymbol->data == '[')
				ret = TRUE;
				break;
	}
	return (ret);
}

int checkBracketMatching(LinkedStack *stack, char *expr)
{
	StackNode	symbol;
	StackNode	*checksymbol;
	int	flag = TRUE;

	while (expr && flag)
	{
		symbol.data = *expr;
		switch (symbol.data)
		{
			case '(':
			case '[':
			case '{':
				push(stack, symbol);
				break;
			case ')':
			case ']':
			case '}':
			if (isLinkedStackEmpty(stack))
				flag = FALSE;
			else
			{
				checksymbol = pop(stack);
				if (!matchSymbol(checksymbol, symbol))
					flag = FALSE;
				free(checksymbol);
				checksymbol = NULL;
			}
			break;
		}
		expr++;
	}
	if (!isLinkedStackEmpty(stack))
		flag = FALSE;
	return flag;
}