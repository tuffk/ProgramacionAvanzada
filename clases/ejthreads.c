/*
compilar 
gcc   ARCHIVO -std=c11 -lpthreads
*/
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#define N 100

void* suma(void*arg);

//int i;
int main()
{
    //pthread_t tid;
    int numhilos=0;
    printf("cuanto shilos a crear\n");
    scanf("%d",&numhilos);
    
    pthread_t* tids= (pthread_t*)malloc(numhilos*sizeof(pthread_t));
    
    for(int i=0; i <numhilos;++i)
    {
        printf("creando hilo %d\n",i);
        pthread_create((tids+i),NULL,suma,i);
    }
    
    //hilo principla
    
    for(int i=0; i <numhilos;++i)
    {
        pthread_join(*(tids+i),NULL);
        printf("terminando el hilo %d \n",i);
    }
    
    
    return 0;
}


void* suma(void*arg)
{
    
        printf("soy el HIJO %d\n",arg);
    
    
    pthread_exit(NULL);
}