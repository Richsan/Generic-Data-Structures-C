/*
	Author: Henrique Manoel (Rich-San) - Brazilian from São Paulo-SP
	Creation date: Date: 24/12/2014
	Github: https://github.com/Richsan

*/
#include "StaticStack.h"

#define STACKPUSH_FULL_ERROR  "\nError: Stack is full, not possible push!\nAborting\n"
#define STACKPOP_EMPTY_ERROR  "\nError: Stack is empty, not possible pops!\nAborting\n"
#define STACKTOP_EMPTY_ERROR  "\nError: Stack is empty, not possible returns top-element!\nAborting\n"
#define MALLOC_ERROR          "\nError: malloc failed at the %s function.\nAborting...\n"  
#define CALLOC_ERROR          "Error: calloc failed at the %s function.\nAborting...\n"
#define SETLENGTH_ERROR_MSG "\nError: There's more elements inside the StaticStack than the new length that you've specified, impossible set to this lenght.\nAborting...\n"
#define REALLOC_ERROR_MSG "\nError: realloc failed at the %s function.\nAborting...\n"
	
void initStaticStack(staticStack * const s, const unsigned int maxSize){
	s->maxSize = maxSize;
	s->top = 0;
	s->stackElement = calloc(maxSize , sizeof(Data));

	if(s->stackElement == NULL)
	{
		printf(CALLOC_ERROR, "initStaticStack");
		exit(1);
	}
}
static void _staticPush(staticStack * const s,Data elem, const unsigned int size){
	
	if(s->top < s->maxSize)
	{
		void * newElement = malloc(size);
		
		if(newElement == NULL)
		{
			printf(MALLOC_ERROR, "staticPush");
			freeStaticStack(s);
			exit(1);
		}

		attribContentVoid(newElement, elem, size);
		
		if(s->stackElement[s->top] != NULL)
			free(s->stackElement[s->top]);


		s->stackElement[s->top] = newElement;
		
		(s->top)++;

		return;
	}
	printf(STACKPUSH_FULL_ERROR);
	exit(1);


}
static Data _staticPop(staticStack * const s){

	if(staticStackIsEmpty(s))
	{	
		printf(STACKPOP_EMPTY_ERROR);
		exit(1);
	}
	
	if((s->top+1) < s->maxSize && s->stackElement[(s->top)+1] != NULL)
	{
		free(s->stackElement[(s->top)+1]);
		s->stackElement[(s->top)+1] = NULL;
	}
	return s->stackElement[--(s->top)];

}
static Data _staticTop(staticStack const *s){
	if(staticStackIsEmpty(s))
	{
		printf(STACKTOP_EMPTY_ERROR);
		exit(1);
	}

	return s->stackElement[(s->top) - 1];

}
bool staticStackIsEmpty(staticStack const *s){

	return s->top <= 0;

}
void freeStaticStack(staticStack * const s){
	int i;

	if((s->top+1) < s->maxSize)
		i = s->top + 1;
	else
		i = s->top;

	if(s->top == s->maxSize)
		i--;

	for(; i >= 0; i--)
		if(s->stackElement[i] != NULL)
			free(s->stackElement[i]);
	
	free(s->stackElement);
}

void setStaticStackLength(staticStack * const s, unsigned int length)
{
	int i;
	Data *temp;
	if(length < s->top)
	{
 		printf(SETLENGTH_ERROR_MSG);
     
      	freeStaticStack(s);
      	exit(0);
	}

	temp = realloc(s->stackElement, length * sizeof(void *));

	if(temp == NULL)
	{
	   printf(REALLOC_ERROR_MSG, "setStaticStackLength");
	   exit(0);
	}
	s->stackElement = temp;
	s->maxSize = length;

	//if the current position memory has not been free yet
	if(s->top < s->maxSize && s->stackElement[s->top] != NULL)
		free(s->stackElement[s->top]);

	for(i = s->top; i < s->maxSize; i++)
		s->stackElement[i] = NULL;


}

_FUNC_PTRPUSH _getPTR_StaticPush(){
	return _staticPush;
}

void _staticPopGet(staticStack *s, Data variable,const unsigned int size){
	attribContentVoid(variable,_staticPop(s), size);
}
void _staticTopGet(staticStack *s, Data variable,const unsigned int size){
	attribContentVoid(variable,_staticTop(s), size);
}
bool staticStackIsFull(staticStack const *s){
	return s->top >= s->maxSize;
}
_FUNC_PTRPOP _getPTR_StaticPop(){
	return _staticPop;
}
_FUNC_PTRTOP _getPTR_StaticTop(){
	return _staticTop;
}
_FUNC_PTRPOPGET _getPTR_StaticPopGet(){
	return _staticPopGet;
}
_FUNC_PTRTOPGET _getPTR_StaticTopGet(){
	return _staticTopGet;
}

