// tour de francia
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ciclistas 10
#define etapas 10 
#define kms 1000

int main()
{
    double time=0;
    int tid;
    int sum;
    int a=0;
    int tiempos[ciclistas];
    
    #pragma omp parallel private(time,sum,a,tid) num_threads(ciclistas)
    {
        #pragma for
        time = omp_get_wtime(); 
        for(int i =0;i<kms;++i)
        {
            a+=i;
        }
        time = omp_get_wtime()- time;
        tiempos[omp_get_thread_num()]=time;
        printf("soy:%d y mi timepo fue %f\n",tid=omp_get_thread_num(),time);
    }
    
    
    return 0;
}