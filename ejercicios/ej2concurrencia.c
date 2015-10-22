#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int kuz;
pthread_mutex_t zain = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t zain;

void* suma(void*arg)
{
    //sleep(1);
    
        for(int i=0;i<10000;++i)
        {
            pthread_mutex_lock(&zain);
            //region critica init
            kuz= kuz +1;
            //region critica end
            pthread_mutex_unlock(&zain);
        }
    
    pthread_exit(NULL);
}


void* resta(void*arg)
{
    
   for(int i=0;i<10000;++i)
        {
            pthread_mutex_lock(&zain);
            //region critica init
            kuz= kuz-1;
            //region critica end
            pthread_mutex_unlock(&zain);
        }
    
    pthread_exit(NULL);
}

int main()
{
    kuz =0;

    /*
    */
    
    pthread_t* tids= (pthread_t*)malloc(2*sizeof(pthread_t));
    pthread_create((tids),NULL,suma,0);
    pthread_create((tids+1),NULL,resta,1);
    
    pthread_join(*(tids),NULL);
    pthread_join(*(tids+1),NULL);
    
    printf("valor final de kuz ocn mutex : %d\n",kuz);
    
    return 0;
}
