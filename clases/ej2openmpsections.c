#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000
int main()
{
  long long int tid,i,suma;
  suma=0;
  double kuz,zain;
  kuz = omp_get_wtime(); 
  double inicio, fin;
  double A[N], B[N], S[N], P[N];
  
  //inicializando vectores
  for( i=0;i<N;++i)
  {
      A[i] = i * 1.75;
      B[i] = i * 0.58;
  }
  
  omp_set_nested(1);//para ahcer paralelismo anidado. tener regiones paralelas DENTRO de regiones paralelas
  
#pragma omp parallel private(tid, i ) num_threads(2) //reduction(+:suma)
  {
    //tid=omp_get_thread_num();
    
    #pragma omp sections
    {
    
#pragma omp section
    for(i=0;i<N;++i)
    {
        P[i]= A[i] * B[i];
    }
#pragma omp section 
    for(i=0;i<N;++i)
    {
        S[i]= A[i] + B[i];
    }
  }
  }
  zain=omp_get_wtime(); 
  printf("tarde %f\n",(zain-kuz));
  
  return 0;
}