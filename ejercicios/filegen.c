#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
      srand((int)time(NULL));
 
       FILE * fp;
       //char * line = NULL;
       int line;
       int cont=0;
       
       fp = fopen("nums", "wb");
       for(;cont<100000;cont++)
       {
	line = rand()%100;
	fprintf(fp,"%d\n", line);
       }
       
 
  return 0;
}