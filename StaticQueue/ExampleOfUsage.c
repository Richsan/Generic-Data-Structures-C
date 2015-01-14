//for compile it, in Generic-Data-Structures-C's directory:
//  gcc VoidFunctions/VoidFunctions.c StaticQueue/StaticQueue.c StaticQueue/ExampleOfUsage.c -o example
//Execute with: ./example (linux) or example.exe (windows)

#include "StaticQueue.h"

int main(){

	staticQueue fila;
	int i;

	createStaticQueue(&fila, 5);

	float b = 2.345;

	enStaticQueue(fila, &b);
	i = 2;
	enStaticQueue(fila, &i);
	enStaticQueue(fila, &i);
	i = 3;
	enStaticQueue(fila, &i);
	enStaticQueueLiteral(fila, 'c', char);
	
	printf("%f\n",deStaticQueue(fila, float));
	printf("%d\n",deStaticQueue(fila, int));
	deStaticQueue(fila,int);
	printf("%d\n", deStaticQueue(fila, int));
	printf("%c\n", deStaticQueue(fila,char));

	/*for(i = 0; i < 3; i++)
	printf("%d\n", deQueue(fila,int));*/

	//deQueue(fila, int);
	
	destroyStaticQueue(fila);
	return 0;
}
