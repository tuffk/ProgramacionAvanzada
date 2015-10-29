#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define SILLAS 20
#define SALAS 7
#define movil 2
#define web 2
#define taquillas 3
//#define GUESTS 5
#define VERE 15

int cine[SALAS][SILLAS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t kuz = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consume_t = PTHREAD_COND_INITIALIZER;
pthread_cond_t sits = PTHREAD_COND_INITIALIZER;
pthread_cond_t produce_t = PTHREAD_COND_INITIALIZER;

void compra(void* arg)
{
    int sala,silla;
    int cont =VERE;
    
    while(cont>0)
    {
        sala = rand()%SALAS;
        silla = rand()%SILLAS;
        
        printf("soy %d, voy a la sala %d, y a la silla %d \n", (int)arg,sala,silla);
        
        pthread_mutex_lock(&kuz);
        if(cine[sala][silla]==0)
        {
            cine[sala][silla]=1;
            printf("soy %d, voy a la sala %d, y a la silla %d YA RESERVE\n", (int)arg,sala,silla);
            cont--;
        }
        else
        {
            printf("soy %d, voy a la sala %d, y a la silla %d ESTABAN OCUPADOS\n", (int)arg,sala,silla);
        }
        pthread_mutex_unlock(&kuz);
        
    }
    printf("vi %d peliculas y me voy\n",VERE);
}


int main()
{
    int GUESTS = taquillas+movil+web;
    srand((int)time(NULL));
    pthread_mutex_lock(&kuz);
    for(int i=0;i<SALAS;++i)
    {
        for(int j=0; j<SILLAS;++j)
        {
            cine[i][j]=0;
        }
    }
    pthread_mutex_unlock(&kuz);
    
    pthread_t * compradores = (pthread_t *) malloc (sizeof(pthread_t) * GUESTS);
    
    int indice = 0;
    
    pthread_t * aux;
    
    /* Crear los productores */
    for (aux = compradores; aux < (compradores+GUESTS); ++aux) {
        printf("comprador: %d \n", ++indice);
        pthread_create(aux, NULL, compra, (void *) indice);
    }
    
    
    for (aux = compradores; aux < (compradores+GUESTS); ++aux) {
        pthread_join(*aux, NULL);
    }
    
    return 0;
}