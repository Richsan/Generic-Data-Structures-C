/*
	Author: Henrique Manoel (Rich-San) - Brazilian from São Paulo-SP
	Creation date: Date: 24/12/2014
	Github: https://github.com/Richsan

*/
#include "StaticStack.h"

void initStaticStack(staticStack *s, const int maxSize){
	s->maxSize = maxSize;
	s->top = 0;
	s->stackElement = calloc(maxSize , sizeof(Data));

}
static void _staticPush(staticStack * const s,Data elem, const int size){
	

	if(s->top < s->maxSize)
	{
		void * newElement = malloc(size);
		attribContentVoid(newElement, elem, size);
		
		if(s->stackElement[s->top] != NULL)
			free(s->stackElement[s->top]);


		s->stackElement[s->top] = newElement;
		
		(s->top)++;

		return;
	}
	printf("Stack is full, not possible push!\n");
	exit(1);


}
static Data _staticPop(staticStack * const s){

	if(staticStackIsEmpty(s))
	{	printf("\nStack is empty, not possible pops!\n");
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
		printf("\nStack is empty, not possible returns top-element!\n");
		exit(1);

	}
	return s->stackElement[(s->top) - 1];

}
bool staticStackIsEmpty(staticStack const *s){

	return s->top <= 0;

}
void freeStaticStack(staticStack *s){
	int i;

	if((s->top+1) < s->maxSize)
		i = s->top + 1;
	else
		i = s->top;

	for(; i >= 0; i--)
		if(s->stackElement[i] != NULL)
			free(s->stackElement[i]);
	free(s->stackElement);
}
_FUNC_PTRPUSH _getPTR_StaticPush(){
	return _staticPush;
}

void _staticPopGet(staticStack *s, Data variable, unsigned int size){
	attribContentVoid(variable,_staticPop(s), size);
}
void _staticTopGet(staticStack *s, Data variable, unsigned int size){
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

