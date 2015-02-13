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
#define staticPop(stack, type) (*(type *)(_getPTR_StaticPop()(stack)))
#define staticTop(stack, type) (*(type *)(_getPTR_StaticTop()(stack)))
#define staticPush(stack, element) (_getPTR_StaticPush()(stack, element, sizeof(element)))
#define staticPopGet(stack, var)  (_getPTR_StaticPopGet()(stack, var, sizeof(*var)))
#define staticTopGet(stack, var)  (_getPTR_StaticTopGet()(stack, var, sizeof(*var)))

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


// stack's structure
typedef void * Data;
typedef struct staticStack staticStack;
struct staticStack
{
	
	unsigned int maxSize;
	unsigned int top;
	Data * stackElement;
	
};

//accessible functions
void initStaticStack(staticStack * const s, const unsigned int maxSize);
bool staticStackIsEmpty(staticStack const *s);
bool staticStackIsFull(staticStack const *s);
void freeStaticStack(staticStack * const s);

//macro only access functions
static void _staticPush(staticStack * const s,Data elem, const unsigned int size); //use macro instead of this,also has an option for literals with macro too ,see above
static Data _staticPop(staticStack * const s); //use macro pop instead of this, never get the memory address, it can be free in next push or pop
static void _staticPopGet(staticStack *s, Data variable,const unsigned int size); //for you pop the value inside a variable
static Data _staticTop(staticStack const * s); //use macro top instead of this, never get the memory address, it can be free in next push or pop
static void _staticTopGet(staticStack *s, Data variable,const unsigned int size); //for you put the top value inside a variable


//static access definitions
typedef void (*_FUNC_PTRPUSH)(staticStack *s,Data elem, const unsigned int size);
typedef Data (* _FUNC_PTRPOP)(staticStack * const s);
typedef Data (* _FUNC_PTRTOP)(staticStack  const * s);
typedef void (* _FUNC_PTRPOPGET)(staticStack *s, Data variable,const unsigned int size);
typedef void (* _FUNC_PTRTOPGET)(staticStack *s, Data variable,const unsigned int size);

_FUNC_PTRPUSH _getPTR_StaticPush();
_FUNC_PTRPOP _getPTR_StaticPop();
_FUNC_PTRTOP _getPTR_StaticTop();
_FUNC_PTRPOPGET _getPTR_StaticPopGet();
_FUNC_PTRTOPGET _getPTR_StaticTopGet();


#endif
