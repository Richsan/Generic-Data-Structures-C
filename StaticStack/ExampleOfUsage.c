//for compile it, in Generic-Data-Structures-C's directory:
//  gcc VoidFunctions/VoidFunctions.c StaticStack/StaticStack.c StaticStack/ExampleOfUsage.c -o example
//Execute with: ./example (linux) or example.exe (windows)

#include "StaticStack.h"

int main(){
	staticStack pilha;
	int i;
	int popValue;
	int topValue;
	initStaticStack(&pilha, 7);

	staticPushLiteral(&pilha, 122.456f, float); //just for values outside a variable

	for(i = 0; i < 6; i++)
		staticPush(&pilha, &i); //just for values inside a variable

	//two manners for get the top value inside a variable
	//1 - attribution (need specify the type value)
	topValue = staticTop(&pilha, int);
	printf("ValueTop-attribution: %d\n", topValue);
	
	//2-using topGet
	staticTopGet(&pilha,&topValue);
	printf("Value-top-topGet: %d\n", topValue);

	//the same for pop values
	//1 - attribution (need specify the type value)
	popValue = staticPop(&pilha, int);
	printf("PopValue-attribution: %d\n", popValue);
	
	//2-using popGet
	staticPopGet(&pilha, &popValue);
	printf("PopValue-popGet: %d\n", popValue);

	for(i = 0; i < 4; i++)
		printf("%d ",staticPop(&pilha, int));


	printf("%.3f\n", staticPop(&pilha, float));

	freeStaticStack(&pilha);

	return 0;
}
