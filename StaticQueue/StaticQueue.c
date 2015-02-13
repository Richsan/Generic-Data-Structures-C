/*
	Author: Henrique Manoel (Rich-San) - Brazilian from São Paulo-SP
	Creation Date: 14/01/2015
	Github: https://github.com/Richsan

*/

#include "StaticQueue.h"

#define QUEUEEN_FULL_ERROR "\nStaticQueue is Full!Impossible insert Queue's element.\nAborting...\n"
#define QUEUEDE_EMPTY_ERROR "\nStaticQueue is empty!Impossible remove Queue'element.\nAborting...\n"
#define MALLOC_ERROR_MSG "\nError: malloc failed at the %s's function.\nAborting...\n" 
#define CALLOC_ERROR_MSG "\nError: calloc failed at the %s's function.\nAborting...\n"

void createStaticQueue(staticQueue * const q, const int  nElem){

	*q = (staticQueue) malloc(sizeof(struct Staticqueue));

	if(*q == NULL)
	{
		printf(MALLOC_ERROR_MSG, "createStaticQueue");
		exit(1);
	}

	(*q)->elem = calloc((nElem+ 1) , sizeof(void *));

	if((*q)->elem == NULL)
	{
		printf(CALLOC_ERROR_MSG, "createStaticQueue");
		exit(1);
	}

	(*q)->qtElements = nElem+1;
	(*q)->front = 0;
	(*q)->rear = 0;
}

void destroyStaticQueue(staticQueue q){
	int i;

	for(i = 0; i < q->qtElements; i++)
		if(q->elem[i] != NULL)
			free(q->elem[i]);

	free(q->elem);
	free(q);
}

bool staticQueueIsEmpty(staticQueue const q){

	return q->front == q->rear;
}

bool staticQueueIsFull(staticQueue const q){

	return ((q->rear + 1) == (q->front)) || (q->front == 0 && q->rear + 1 == q->qtElements);
}

static void _enStaticQueue(staticQueue q,void * const elem, const unsigned int size){

	void * content;
	if(staticQueueIsFull(q))
	{
		printf(QUEUEEN_FULL_ERROR);
		exit(0);
	}

	content = malloc(size);

	if(content == NULL)
	{
		printf(MALLOC_ERROR_MSG, "enStaticQueue");
		destroyStaticQueue(q);
		exit(1);
	}

	attribContentVoid(content,elem,size);
	
	if(q->elem[q->rear] != NULL)
		free(q->elem[q->rear]);

	q->elem[q->rear] = content;	
	
	if(q->rear + 1 == q->qtElements)
		q->rear = 0;

	else
		q->rear++;
	
}
static void * _deStaticQueue(staticQueue q){
	void * elem;
	
	
	if(staticQueueIsEmpty(q))
	{
		printf(QUEUEDE_EMPTY_ERROR);
		exit(0);
	}

	if((q->front-1) >= 0 && (q->front-1) != q->rear && q->elem[q->front-1] != NULL)
	{
		free(q->elem[q->front-1]);
		q->elem[q->front-1] = NULL;
	}
	if((q->front -1) == -1 && q->rear != (q->qtElements-1) && q->elem[q->qtElements-1] != NULL)
	{
		free(q->elem[q->qtElements-1]);
		q->elem[q->qtElements-1] = NULL;
	}
	
	elem = q->elem[q->front];

	if(q->front + 1 == q->qtElements)
		q->front = 0;
	
	else
		q->front++;

	return elem;	
}
static void _deStaticQueueGet(staticQueue q, void * const elem, const unsigned int size){

	attribContentVoid(elem,_deStaticQueue(q),size);	
}

_FUNC_PTRENSTATICQUEUE _getPTR_EnStaticQueue(){
	return _enStaticQueue;
}
_FUNC_PTRDESTATICQUEUE _getPTR_DeStaticQueue(){
	return _deStaticQueue;
}
_FUNC_PTRDESTATICQUEUEGET _getPTR_DeStaticQueueGet(){
	return _deStaticQueueGet;
}
