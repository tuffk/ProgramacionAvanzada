#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000
int main()
{
  long long int tid,i,suma;
  suma=0;
  double kuz,zain;
  kuz = omp_get_wtime(); 
#pragma omp parallel private(tid)
  {
    //tid=omp_get_thread_num();
#pragma omp for private(i) reduction(+:suma) schedule(guided,100000)
    for(i=0;i<N;++i)
    {
//#pragma omp atomic
      suma+=i;
    }
  }
  zain=omp_get_wtime(); 
  printf("%lli y tarde %f\n",suma,(zain-kuz));
  
  return 0;
}