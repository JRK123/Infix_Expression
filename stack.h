/* This file contains the type declaration of stack
 * and prototypes of all stack's functions.
 * We say that these function prototypes are "stack interface"
 */ 
#define MAX 128
typedef struct stack {
	int a[MAX];
	int i;
}stack;
/* these prototypes help us avoid the compiler warnings,
 * in any code which calls these functions. 
 */
void push(stack *s, int num);
int pop(stack *s);
int empty(stack *s);
int full(stack *s);
void init(stack *s);


