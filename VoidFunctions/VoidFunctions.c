/*
  Author: Henrique Manoel (Rich-San) - Brazilian from São Paulo-SP
  Github: https://github.com/Richsan

*/
#include "VoidFunctions.h"

void swapVoid(void *a, void *b, unsigned size) {
  char tmp;

  if (a != b)
  {
    while (size--) 
	  {
      tmp = *(char *)a;
      *(char *)a++ = *(char *)b;
      *(char *)b++ = tmp;
    }
  }
}
void attribContentVoid(void *destination, void *source, unsigned int size){
	
	if (source != destination)
	 {
	    while (size--) 
		  *(char *)destination++ = *(char *)source++;
	      
	 }

}