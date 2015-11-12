/*
  ejemplo  con
  * teams
  * num_teams
  *thread_limit
  *private
  *reduction
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>
#define N 10000


int main()
{
  int total[N];
  int i,sum=0;

#pragma omp target map(to:total[:N])
#pragma omp teams num_teams(2) thread_limit(4)

#pragma omp parallel private(i) reduction(+:sum)
  {
#pragma omp for 
    for(i =0; i <= N;++i)
    {
      total[i]= i;
      sum+=i;
    }
    printf("i=%d, num_teams=%d, team_id=%d, num_threads=%d, thread_id=%d, mi suma: %d\n", i,omp_get_num_teams(),omp_get_team_num(),omp_get_num_threads(),omp_get_thread_num(),sum);
  }
  printf("suma(con reduction y private): %d\n",sum);
  
  sum =0;

  #pragma omp target map(to:total[:N])
#pragma omp teams num_teams(2) thread_limit(4)

#pragma omp parallel
  {
#pragma omp for 
    for(i =0; i <= N;++i)
    {
      total[i]= i;
      sum+=i;
    }
    printf("i=%d, num_teams=%d, team_id=%d, num_threads=%d, thread_id=%d, mi suma: %d\n",
i,omp_get_num_teams(),omp_get_team_num(),omp_get_num_threads(),omp_get_thread_num(),sum);
  }
  printf("suma(sin reduction ni private): %d\n",sum);

  return 0;
}