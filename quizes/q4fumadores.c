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
pthread_mutex_t yaharadin = PTHREAD_MUTEX_INITIALIZER;

void agente (void* arg)
{
    int r1=0;
    int r2=0;
    //printf("debugnnnnnnnnnnnnnnnnnnnnn\n");
    while(1){
    pthread_mutex_lock(&zain);
    pthread_mutex_lock(&tutzke);
    pthread_mutex_lock(&yaharadin);
        if(coloca)
        {
            
            coloca=0;
           
            srand(time(NULL));
           
            mm1=rand()%3;
            
            do{
               mm2=rand()%3; 
            }while(mm1==mm2);
            printf("soy el agente y coloque %d y %d\n", mm1,mm2);
        }
        //pthread_mutex_unlock(&tutzke);
        pthread_mutex_unlock(&yaharadin);
        pthread_mutex_unlock(&tutzke);
        pthread_mutex_unlock(&zain);
    }
}

void fumar1(void * arg1)
{
    
    int mine1;
    mine1= ((int*)(arg1));
    while(1){
    //printf("soy el fumador %d, y me dio polio\n", mine1);
    pthread_mutex_lock(&zain);
    pthread_mutex_lock(&tutzke);
    pthread_mutex_lock(&yaharadin);
    
    if(mine1 ==mm1 || mine1==mm2)
    {
        pthread_mutex_unlock(&yaharadin);
        pthread_mutex_unlock(&tutzke);
        pthread_mutex_unlock(&zain);
        
    }else{
        mm1=-1;
        mm2=-1;
        
        coloca=1;
        pthread_mutex_unlock(&yaharadin);
        pthread_mutex_unlock(&tutzke);
        pthread_mutex_unlock(&zain);
        printf("soy el fumador %d, y me dio caner\n", mine1);
    }
}
pthread_exit(NULL);
}

void fumar2(void * arg2)
{
    
    int mine2;
    mine2= ((int*)(arg2));
    while(1){
    //printf("soy el fumador %d, y me dio polio\n", mine2);
    pthread_mutex_lock(&zain);
    pthread_mutex_lock(&tutzke);
    pthread_mutex_lock(&yaharadin);
    
    if(mine2 ==mm1 || mine2==mm2)
    {
        pthread_mutex_unlock(&yaharadin);
        pthread_mutex_unlock(&tutzke);
        pthread_mutex_unlock(&zain);
        
    }else{
        mm1=-1;
        mm2=-1;
        
        coloca=1;
        pthread_mutex_unlock(&yaharadin);
        pthread_mutex_unlock(&tutzke);
        pthread_mutex_unlock(&zain);
        printf("soy el fumador %d, y me dio caner\n", mine2);
    }
}
pthread_exit(NULL);
}

void fumar3(void * arg3)
{
    
    int mine3;
    mine3= ((int*)(arg3));
    while(1){
    //printf("soy el fumador %d, y me dio polio\n", mine3);
    pthread_mutex_lock(&zain);
    pthread_mutex_lock(&tutzke);
    pthread_mutex_lock(&yaharadin);
    
    if(mine3 ==mm1 || mine3==mm2)
    {
        pthread_mutex_unlock(&yaharadin);
        pthread_mutex_unlock(&tutzke);
        pthread_mutex_unlock(&zain);
        
    }else{
        mm1=-1;
        mm2=-1;
        
        coloca=1;
        pthread_mutex_unlock(&yaharadin);
        pthread_mutex_unlock(&tutzke);
        pthread_mutex_unlock(&zain);
        printf("soy el fumador %d, y me dio caner\n", mine3);
    }
}
pthread_exit(NULL);
}

int main()
{
    mm1 = PAPEL;
    mm2 = CERILLOS;
    coloca=0;
    pthread_t* tids= (pthread_t*)malloc(4*sizeof(pthread_t));
    pthread_create((tids),NULL,agente,1);
    pthread_create((tids+1),NULL,fumar1,PAPEL);
    pthread_create((tids+2),NULL,fumar2,TABACO);
    pthread_create((tids+3),NULL,fumar3,CERILLOS);
    
    pthread_join(*(tids),NULL);
    pthread_join(*(tids+1),NULL);
    pthread_join(*(tids+2),NULL);
    pthread_join(*(tids+3),NULL);
    
    
    return 0;
}