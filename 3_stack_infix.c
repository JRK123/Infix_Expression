#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "stack.h"
#include "cstack.h"

#define OPERAND 10 
#define OPERATOR 20
#define END     30
#define BRACKET 40
#define BRACKET_END 50
//#define ERROR   40

int readline(char *arr, int len) {
	int j = 0;
	int ch;
	while((ch = getchar()) != '\n' && j < len - 1) {
		if(ch == ' ')
		{
			continue;
		}
		else
		{
			arr[j] = ch;
			j++;
		}
	}
	
	arr[j] = '\0';
	return j;
}

typedef struct token {
	int type;
	int nos;
	char op;
}token; 
static int i = 0;
token *getnext(char *str)
{

	token *t = (token *)malloc(sizeof(token));	
	switch(str[i])
	{									
		case '1': case '2': case '3': 
		case '4': case '5': case '6': 
		case '7': case '8': case '9': 
		case '0': 
			t->type = OPERAND;
			t->nos = str[i] - '0';
			i++;
			return t;
			break;
		
		case '+': case '-': case '*': 
		case '/': case '%': case ')':
		case '(':
			
			t->type = OPERATOR;
			t->op = str[i];
			i++;
			return t;
			break;

		case '\0':
			t->type = '?';
			return t;
			break;
	}	
	
}

int precedence(char op) {
        if(op == '%')
                return 4;
        if(op == '*' || op == '/')
                return 3;
        if(op == '+' || op == '-')
                return 2;
	if(op == '#')
		return 1;
        
}

static int k = 0;
int infixval(char *infix)
{
	token *t;
	stack a;
	char x, y;
	int p1, p2, j = 0, result = 10, resultin = 1, m, n;
	init(&a);
	cstack b;
	cinit(&b);
	cpush(&b, '#');
	k = 0;
	while(1)
	{	
		t = getnext(infix);
		if(t->type == OPERAND)
		{	
			k = k*10 + t->nos;		
			continue;	
		}

	
		else if(t->type == OPERATOR)
		{
			if(t->op == '+' || t->op == '-' ||t->op == '*' || t->op == '/' || t->op == '%')
			{
				
				push(&a, k);
				if(pop(&a) == '@') {
				}
				else {
					push(&a, k);
					k = 0;
				}
				x = cpop(&b);
				p1 = precedence(x);
				y = t->op;
				p2 = precedence(y);
				if(p1 >= p2)
				{
					n = pop(&a);
					m = pop(&a);
					switch(x)
					{
						case '+':
							result = m + n;
							break;
						case '-':
							result = m - n;
							break;
						case '*':
							result = m * n;
							break;
						case '/':
							result = m / n;
							break;
						case '%':
							result = m % n;
							break;
					}
					push(&a, result);
					cpush(&b, y);							
				}
				else if(p1 < p2)
				{
					cpush(&b, x);
					cpush(&b, y);		
				}
				continue;
			}
			else if(t->op == '(')
			{
				result = infixval(infix);
				push(&a, result);
				k = '@';
				continue;
			}
			else if(t->op == ')')
			{
				
				push(&a, k);
				if(pop(&a) == '@') {
				}
				else
					push(&a, k);
				while(1)
				{	
					x = cpop(&b);
					if(x == '#')
					{
						n = pop(&a);
						return n;	
					}
					n = pop(&a);
					m = pop(&a);
					
					switch(x)
					{	
						
						case '+':
							result = m + n;
							break;
						case '-':
							result = m - n;
							break;
						case '*':
							result = m * n;
							break;
						case '/':
							result = m / n;
							break;
						case '%':
							result = m % n;
							break;
					}
					push(&a, result);
					result = pop(&a);
					if(!empty(&a))
					{
						push(&a, result);
						continue;
					}
					else 
						return result;
				}	
			}
		continue;
		
		}



		else if(t->type == '?') 
		{
			push(&a, k);
			
			if(pop(&a) == '@') {
				
			}

			else
				push(&a, k);

			while(1)
			{	
				x = cpop(&b);
				if(x == '#')
				{
					n = pop(&a);
					return n;	
				}
				n = pop(&a);
				m = pop(&a);
				
				switch(x)
				{	
					
					case '+':
						result = m + n;
						break;
					case '-':
						result = m - n;
						break;
					case '*':
						result = m * n;
						break;
					case '/':
						result = m / n;
						break;
					case '%':
						result = m % n;
						break;
				}
				push(&a, result);
				result = pop(&a);
				if(!empty(&a))
				{
					push(&a, result);
					continue;
				}
				else 
					return result;
			}	
		}	
	}
}

int main()
{
	
	char str[1024];	
	int ans = 1, x = 0;
	while(x != -1)
	{
		x = readline(str, 1024);	
		ans = infixval(str);
		printf("%d\n", ans);
		i = 0;
		k = 0;
	}
	return 0;
	
}
