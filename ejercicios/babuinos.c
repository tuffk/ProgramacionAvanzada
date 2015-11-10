#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define L 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int cuerda[L];

int este;
int oeste;

void * cruzar(void * arg)
{
    while(1)
    {
        //pthread_mutex_lock(&mutex);
        if(este <=0 && oeste<=0)
        {
            break;
        }
        //pthread_mutex_unlock(&mutex);
        
        pthread_mutex_lock(&mutex2);
        if((oeste)>este)
        {
            if(oeste>0)
            oeste--;
        }else{
            if(este>0)
            este--;
        }
        printf("t:%d--hay %d estudiantes de comunicacoin en el ESTE y %d en el OESTE\n",(int)arg,este,oeste);
        pthread_mutex_unlock(&mutex2);
        //pthread_mutex_lock(&mutex);
        if(este <=0 && oeste<=0)
        {
            break;
        }
        //pthread_mutex_unlock(&mutex);
        
    }
    pthread_exit(NULL);
}


int main ()
{
    este = oeste =0;
    srand((int) time(NULL));
    
    este = rand()%500;
    oeste = rand()%500;
    int indice = 0;
    pthread_t * babuinos = (pthread_t *) malloc (sizeof(pthread_t) * 5);
    printf("hay %d estudiantes de comunicacoin en el ESTE y %d en el OESTE\n",este,oeste);
    
    pthread_create((babuinos), NULL, cruzar, 1);
    pthread_create((babuinos+1), NULL, cruzar, 2);
    pthread_create((babuinos+2), NULL, cruzar, 3);
    pthread_create((babuinos+3), NULL, cruzar, 4);
    pthread_create((babuinos+4), NULL, cruzar, 5);
    
    pthread_join(*babuinos, NULL);
    pthread_join(*(babuinos+1), NULL);
    pthread_join(*(babuinos+2), NULL);
    pthread_join(*(babuinos+3), NULL);
    pthread_join(*(babuinos+4), NULL);
    free(babuinos);
    
    return 0;
}