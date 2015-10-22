#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#define PAPEL 0
#define TABACO 1
#define CERILLOS 2

int material;
int mm1;
int mm2;
int coloca;

pthread_mutex_t zain = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tutzke = PTHREAD_MUTEX_INITIALIZER;

void agente (void* arg)
{
    int r1=0;
    int r2=0;
    while(1){
        pthread_mutex_lock(&tutzke);
        if(coloca)
        {
            
            coloca=0;
            pthread_mutex_unlock(&tutzke);
            srand(time(NULL));
            mm1=rand()%3;
            
            do{
               mm2=rand()%3; 
            }while(mm1==mm2);
        }
        pthread_mutex_unlock(&tutzke);
    }
}

void fumar(void * arg)
{

    int mine;
    mine= *((int*)(arg));
    pthread_mutex_lock(&zain);
    if(mine ==mm1 || mine==mm2)
    {
        pthread_mutex_unlock(&zain);
    }else{
        mm1=-1;
        mm2=-1;
        pthread_mutex_unlock(&zain);
        pthread_mutex_lock(&tutzke);
        coloca=1;
        pthread_mutex_unlock(&tutzke);
        printf("soy el fumador %d, y me dio caner", mine);
    }
}

int main()
{
    mm1 = mm2 =0;
    coloca=1;
    pthread_t* tids= (pthread_t*)malloc(4*sizeof(pthread_t));
    pthread_create((tids),NULL,agente,1);
    pthread_create((tids+1),NULL,fumar,PAPEL);
    pthread_create((tids+2),NULL,fumar,TABACO);
    pthread_create((tids+3),NULL,fumar,CERILLOS);
    
    pthread_join(*(tids),NULL);
    pthread_join(*(tids+1),NULL);
    pthread_join(*(tids+2),NULL);
    pthread_join(*(tids+3),NULL);
    return 0;
}