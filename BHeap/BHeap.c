/*
   Author: Henrique Manoel (Rich-San) - Brazilian from São Paulo-SP
   Creation Date: 12/02/2015
   Github: https://github.com/Richsan

*/

#include "BHeap.h"


#define MALLOC_ERROR_MSG "\nError: malloc failed at the %s's function.\nAborting...\n" 
#define CALLOC_ERROR_MSG "\nError: calloc failed at the %s's function.\nAborting...\n"
#define SETLENGTH_ERROR_MSG "\nError: There's more elements inside the BHeap than the new length that you've specified, impossible set to this lenght.\nAborting...\n"
#define REALLOC_ERROR_MSG "\nError: realloc failed at the %s's function.\nAborting...\n"
#define FULLHEAP_ERROR_MSG "\nError: Heap is full, impossible push element!\nAborting...\n"
#define EMPTYHEAP_ERROR_MSG "\nError: Heap is empty, impossible pop element!\nAborting...\n"


void createBHeap(bHeap * const h,const unsigned int maxSize, conditionFunction func)
{
   *h = malloc(sizeof(struct _heap));

   if(*h == NULL)
   {
      printf(MALLOC_ERROR_MSG, "createBHeap");
      exit(0);
   }

   (*h)->data = calloc((maxSize+1), sizeof(void *));

   if((*h)->data == NULL)
   {
      printf(CALLOC_ERROR_MSG, "createBHeap");
      exit(0);
   }

   (*h)->maxSize = maxSize+1;
   (*h)->currentSize = BHEAP_ROOT;
   (*h)->isParent = func;
}
void destroyBHeap(bHeap h)
{

  if(h->currentSize < h->maxSize && h->data[h->currentSize] != NULL)
      free(h->data[h->currentSize]);
   
   h->currentSize--;

   while(h->currentSize > 0)
   {
      free(h->data[h->currentSize]);
      h->currentSize--;
   }
  
   free(h->data);
   free(h);
}
static void swapBHeap(bHeap h,const unsigned int index1,const unsigned int index2)
{
   void * temp = h->data[index1];
   h->data[index1] = h->data[index2];
   h->data[index2] = temp;
}
static void upBHeap(bHeap h, unsigned int indexNode)
{
   while(indexNode > BHEAP_ROOT)
   {
      if(!h->isParent(h->data[BHEAP_PARENT(indexNode)] , h->data[indexNode]))
      {
	     swapBHeap(h, indexNode, BHEAP_PARENT(indexNode));
	     indexNode = BHEAP_PARENT(indexNode);
	     continue;
      }
      break;
   }
}
bool isBHeapLeaf(bHeap h,const unsigned int index)
{
   if(BHEAP_LEFTCHILD(index) >= h->currentSize)
      return true;
   if(BHEAP_RIGHTCHILD(index) >= h->currentSize && h->data[BHEAP_LEFTCHILD(index)] == NULL)
      return true;
   if(BHEAP_RIGHTCHILD(index) >= h->currentSize && h->data[BHEAP_LEFTCHILD(index)] != NULL)
      return false;

   if(h->data[BHEAP_RIGHTCHILD(index)] == NULL && h->data[BHEAP_LEFTCHILD(index)] == NULL)
      return true;

   return false;
}

void setBHeapLength(bHeap h,unsigned int length)
{
   int i;
   void **temp;
   if(length < h->currentSize)
   {
      printf(SETLENGTH_ERROR_MSG);
     
      destroyBHeap(h);
      exit(0);
   }
   
   
   temp = realloc(h->data, (length+1) * sizeof(void *));
   
   if(temp == NULL)
   {
      printf(REALLOC_ERROR_MSG, "setBHeapLength");
      exit(0);
   }

   h->data = temp;
   h->maxSize = length+1;

   for(i = h->currentSize; i < h->maxSize; i++)
      h->data[i] = NULL;
}

static unsigned int maxNodeBHeap(bHeap h, const unsigned int index1, const unsigned int index2, const unsigned int index3)
{
   int max = index2;
   if(h->isParent(h->data[index1] , h->data[max]))
      max = index1;

   if(h->isParent(h->data[index3] , h->data[max]))
      max = index3;

   return max;
}
static void downBHeap(bHeap h,unsigned int indexNode)
{ 
   if(bHeapIsEmpty(h))
      return;

   while(!isBHeapLeaf(h, indexNode))
   {
      if(BHEAP_RIGHTCHILD(indexNode) >= h->currentSize)
      {
      	 if(!h->isParent(h->data[indexNode] , h->data[BHEAP_LEFTCHILD(indexNode)]))
      	    swapBHeap(h,indexNode,BHEAP_LEFTCHILD(indexNode));
      	 break;
      }
      int max = maxNodeBHeap(h,indexNode, BHEAP_RIGHTCHILD(indexNode), BHEAP_LEFTCHILD(indexNode));

      if(max == indexNode)
	      break;
      else
      {
	      swapBHeap(h,indexNode,max);
	      indexNode = max;
      }
   }
}
static void _pushBHeap(bHeap h, void * const value,const unsigned int size)
{
   
   if(bHeapIsFull(h))
   {
      printf(FULLHEAP_ERROR_MSG);
      destroyBHeap(h);
      exit(0);
   }

   if(h->data[h->currentSize] != NULL)
      free(h->data[h->currentSize]);

   h->data[h->currentSize] = malloc(size);
   
   if(h->data[h->currentSize] == NULL)
   {
      printf(MALLOC_ERROR_MSG, "pushBHeap");
      exit(0);
   }

   attribContentVoid(h->data[h->currentSize] , value, size);

   upBHeap(h, h->currentSize);
   h->currentSize++;   
}
static void * _popBHeap(bHeap h)
{
   if(bHeapIsEmpty(h))
   {
      printf(EMPTYHEAP_ERROR_MSG);
      destroyBHeap(h);
      exit(0);
   }

   if(h->currentSize < h->maxSize && h->data[h->currentSize] != NULL)
    {
      free(h->data[h->currentSize]);
      h->data[h->currentSize] = NULL;
    }  
   
   void * ret = h->data[BHEAP_ROOT];
   h->currentSize--; 
   swapBHeap(h, BHEAP_ROOT, h->currentSize);
     
   downBHeap(h, BHEAP_ROOT);
    
   return ret;
}
bool bHeapIsEmpty(bHeap h)
{
   return h->currentSize == BHEAP_ROOT;
}
bool bHeapIsFull(bHeap h)
{
   return h->currentSize >= h->maxSize;
}

static void  _popBHeapGet(bHeap h, void * const guardVar, const unsigned int size)
{
   attribContentVoid(guardVar, _popBHeap(h),size);
}

_FUNC_PTRPUSHBHEAP _getPTR_PushBHeap()
{
   return _pushBHeap;
}

_FUNC_PTRPOPBHEAP _getPTR_PopBHeap()
{
   return _popBHeap;
}

_FUNC_PTRPOPBHEAPGET _getPTR_PopBHeapGet()
{
   return _popBHeapGet;
}
