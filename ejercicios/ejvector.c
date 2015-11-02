#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#define N 100000


int total=0;
pthread_mutex_t zain = PTHREAD_MUTEX_INITIALIZER;

void hilo(void* arg)
{
       FILE * fp;
       char * line = NULL;
       size_t len = 0;
       ssize_t read;
       int num=0;
       int suma=0;
       int kuz= N/1000;
       kuz=8;//-------------------------------hard code
	int start =0;
	int end =0;
	int cont=0;
       fp = fopen("./nums", "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);
  start = (int)arg * (N/kuz);
  end = start + (N/kuz);
  cont= start;
       printf("start %d,fin %d\n",start,end);
       
       while ((read = getline(&line, &len, fp)) != -1) {
           //printf("Retrieved line of length %zu :\n", read);
           //printf("%s", line);
	 ++cont;
	 if (cont < start)  { continue; }
  if (cont > end) { break; }    // done
  
	    num = (atoi(line));
	    //printf("%d\n",num);
	    suma+=num;
	    
       }
       
       //fclose(fp);
       printf("sume %d\n",suma);
       pthread_mutex_lock(&zain);
       total+=suma;
       pthread_mutex_unlock(&zain);
       pthread_exit(NULL);
}


int main()
{
    int nhilos = N/1000;
    nhilos=8;//---------------------------------------hard code
    pthread_t* tids= (pthread_t*)malloc((nhilos)*sizeof(pthread_t));
    pthread_t* aux=tids;
    clock_t start, end;
    double cpu_time_used;
    int index=0;
    
    start=clock();
     
    for(;aux<(tids+nhilos);++aux)
    {
      
	pthread_create((aux),NULL,hilo,index++);
    }
    
    for(aux=tids;aux<(tids+nhilos);++aux)
    {
      //printf("algo\n");
	pthread_join(*(aux),NULL);
    }
    end=clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("tarde %d\n",cpu_time_used);
    printf("TOTAL: %d\n",total);

return 0;
}