/*
	Author: Henrique Manoel (Rich-San) - Brazilian from São Paulo-SP
	Creation Date: 24/12/2014
	Github: https://github.com/Richsan

*/
#ifndef STATICSTACK_H
#define STATICSTACK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../VoidFunctions/VoidFunctions.h"

//------------Macros for best use---------------------------------------------------
//type is literaly the type of content in stack, and stack is the pointer of staticStack
#define staticPop(stack, type) *(type *)(_getPTR_StaticPop()(stack))
#define staticTop(stack, type) *(type *)(_getPTR_StaticTop()(stack))
#define staticPush(stack, element) _getPTR_StaticPush()(stack, element, sizeof(element))

//A macro for push literals in stack, it's necessary inform literaly the type of the literal
#define staticPushLiteral(stack, element, type)\
	{if((stack)->top < (stack)->maxSize)\
	{\
		type elem = element;\
		void * newElement = malloc(sizeof(type));\
		attribContentVoid(newElement, &elem, sizeof(type));\
		\
		if((stack)->stackElement[(stack)->top] != NULL)\
			free((stack)->stackElement[(stack)->top]);\
\
\
		(stack)->stackElement[(stack)->top] = newElement;\
		\
		((stack)->top)++;}}
//------------------------END of macro function----------------------------------------------

typedef void * Data;
typedef struct staticStack staticStack;
struct staticStack
{
	
	int maxSize;
	int top;
	Data * stackElement;
	
};

void initStaticStack(staticStack *s, const int maxSize);
static void _staticPush(staticStack * const s,Data elem, const int size); //use macro instead of this,also has an option for literals with macro too ,see above
static Data _staticPop(staticStack * const s); //use macro pop instead of this, never get the memory address, it can be free in next push or pop
void staticPopGet(staticStack *s, Data variable, unsigned int size); //for you get the value inside a variable with sizeof function
static Data _staticTop(staticStack const * s); //use macro top instead of this, never get the memory address, it can be free in next push or pop
void staticTopGet(staticStack *s, Data variable, unsigned int size); //for you get the top value inside a variable with sizeof function
bool staticStackIsEmpty(staticStack const *s);
bool staticStackIsFull(staticStack const *s);
void freeStaticStack(staticStack *s);

//static access definitions
typedef void (*_FUNC_PTRPUSH)(staticStack *s,Data elem, const int size);
typedef Data (* _FUNC_PTRPOP)(staticStack * const s);
typedef Data (* _FUNC_PTRTOP)(staticStack  const * s);

_FUNC_PTRPUSH _getPTR_StaticPush();
_FUNC_PTRPOP _getPTR_StaticPop();
_FUNC_PTRTOP _getPTR_StaticTop();


#endif