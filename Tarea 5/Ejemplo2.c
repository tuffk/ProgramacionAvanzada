/*
  teams
  *default
  *firstprivate
  *shared
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>
#define N 10

int main()
{
  int total[N];
  int sum=0;
  int i = 0;
  
#pragma omp target map(to:i)
#pragma omp teams num_teams(2) thread_limit(4)
#pragma omp parallel private(i)
  {
    printf("soy: %d, i vale: %d\n",omp_get_thread_num(),++i);
  }
    
  printf("\n\n\n");
  
  
int j=0;
#pragma omp target map(to:j) 
#pragma omp teams num_teams(2) thread_limit(4)
#pragma omp parallel default(shared)
{

  j+=1;
  printf("soy: %d, j vale: %d\n",omp_get_thread_num(),j);
}
  
  printf("i:%d, j: %d\n",i,j);
    printf("\n\n\n");
    
  #pragma omp target map(to:j)
#pragma omp teams num_teams(2) thread_limit(4)
#pragma omp parallel firstprivate(j)
  {
    printf("soy: %d, j vale: %d\n",omp_get_thread_num(),++j);
  }
  

  return 0;
}