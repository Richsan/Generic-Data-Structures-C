//for compile it, in Generic-Data-Structures-C's directory:
//  gcc VoidFunctions/VoidFunctions.c BHeap/BHeap.c BHeap/ExampleOfUsage.c -o example
//Execute with: ./example (linux) or example.exe (windows)

#include "BHeap.h"



bool func(void *elem1, void *elem2)
{
   return (*(int *)elem1 >= *(int *)elem2);
}
int main()
{
    int opc, cont=0, getValue;
    bHeap h;
    createBHeap(&h, 5, func);
    printf("\nInsert max of five numbers inside the heap:\n");
    printf("Insert -1 for finish the insertion\n\n");
    do{
       
	scanf("%d", &opc);
	if(opc != -1)
	{
	   pushBHeap(h,&opc);
	    cont++;
	}

    }while(opc != -1);

    if(bHeapIsFull(h))
        printf("Heap is Full\n");
    if(bHeapIsEmpty(h))
        printf("Heap is empty\n");

    printf("Increasing heap's length for 10 elements.\n");
    setBHeapLength(h, 10);

    printf("\nInserting literal 1 and 45 inside the heap\n");
    pushLiteralBHeap(h, 1, int);
    pushLiteralBHeap(h, 45, int);
    cont ++;

    printf("\nPops inserted elements:\n");
    for(; cont > 0; cont--)
       printf("%d ",popBHeap(h,int));
   

   printf("\nPop last element with popBHeapGet:\n");
   popBHeapGet(h, &getValue);
   printf("%d\n", getValue);
    printf("\nDestroying the heap\n");
    destroyBHeap(h);
    return 0;
}
