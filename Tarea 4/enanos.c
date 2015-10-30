#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define SILLAS 4
#define ENANOS 7

int mesa[SILLAS];
int sentados=0;
int platos=0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t kuz = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consume_t = PTHREAD_COND_INITIALIZER;
pthread_cond_t sits = PTHREAD_COND_INITIALIZER;
pthread_cond_t produce_t = PTHREAD_COND_INITIALIZER;

void * blancanieves(void * arg)
{
   while(1){
        //usleep(rand() % 500);
        
        pthread_cond_wait(&produce_t, &mutex);
        
        pthread_mutex_lock(&mutex);
        platos++;
        printf("un enano me pidio de comer\n");
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&consume_t);
    }
    pthread_exit(NULL);
}

void * enanitos(void * arg)
{
    while(1)
    {
        usleep(rand() % 500);
        pthread_mutex_lock(&kuz);
        if(sentados<SILLAS)
        {
            sentados++;
            pthread_cond_signal(&produce_t);
            printf("me sente y pedi de comer\n");
        }else{
            printf("esperando a que se pare un enano\n");
            pthread_cond_wait(&sits, &kuz);
            pthread_cond_signal(&produce_t);
            printf("me sente (despues de eperar) y pedi de comer\n");
            sentados++;
        }
        pthread_mutex_unlock(&kuz);
        
        
        pthread_cond_wait(&consume_t, &mutex);        
        pthread_mutex_lock(&mutex);
        platos--;
        sentados--;
        printf("comi me voy a trabajar\n");
        
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&sits);
        
    }
}

int main(int argc, const char * argv[])
{
    int nhilos = ENANOS + 1;
    
    pthread_t * obreros = (pthread_t *) malloc (sizeof(pthread_t) * nhilos);
    
    int indice = 0;
    
    pthread_t * aux;
    
    for (aux = obreros; aux < (obreros+ENANOS); ++aux) {
        printf("--- Creando el enano %d ---\n", ++indice);
        pthread_create(aux, NULL, enanitos, (void *) indice);
        //printf("%p\n",aux);
    }
    
    printf("--- Creando blancanieves ---\n");
    ++indice;
    pthread_create(aux, NULL, blancanieves, (void *) indice);
    //printf("%p\n",aux);
    
    
    for (aux = obreros; aux < (obreros+nhilos); ++aux) {
        pthread_join(*aux, NULL);
    }
    free(obreros);
    return 0;    
}