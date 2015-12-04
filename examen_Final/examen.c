#include <signal.h>
#include "mpi.h"
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 1000
#define ocupadas 5

typedef struct{
  int X[N][N];
} BOARD;

BOARD init(BOARD b);

void gestor(int s);

void imprimela(char res,int fin);

int ii;
char* resul[N][N*N];

int main(int argc, char *argv[])
{
  
  srand((int)time(NULL));
  int myid, numprocs, nh, tid;
  BOARD tablero=init(tablero);
  //printf("x:%d y:%d\n",tablero.X[5],tablero.Y[7]);
  int i =0,j=0;
  for(;i<ocupadas;++i)
  {
    tablero.X[rand()%N][rand()%N]=-1;
  }
  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  
  
  if (myid == 0) //Es el master
    {
      //char res[N][N*N];
      int f=0;
      while(1)
      {
      signal(SIGUSR1,gestor);
      //MPI_Recv(&res[i],1,MPI_CHAR,1,0,MPI_COMM_WORLD,NULL);i++;ii=i;
      
      imprimela(resul,i);
      }
      
    }
    
  int sectores;
  sectores=N/numprocs;
  int startx,starty,endx,endy;
  startx=0;
  starty=0;
  endx=N;
  endy=N;
  char res[N*N];
  
#pragma omp parallel private(startx,starty,endx,endy,i,j)
  {
    #pragma omp for
    for(i=0;i<N;++i)
    {
      strcat(res,"d");

      for(j=0;j<N;++j)
      {
	
	if(tablero.X[i][j]==-1)
	{
	  break;
	}
	strcat(res,"a");
      }
      if(i==(N-1) && j==(N-1))
      {
	//MPI_Send(&res,0,MPI_CHAR,0,0,MPI_COMM_WORLD);
	strcpy(res[ii++],res);
      }
    }
    
  }
  
  
  //MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  MPI_Finalize();
}


BOARD init(BOARD b)
{
  int i=0,j=0;
  for(;i<N;++i)
  {
    for(;j<N;++j)
    {
      b.X[i][j]=0;
    }
  }
  return b;
}

void gestor(int s)
{
  imprimela(resul,ii);
}

void imprimela(char res,int fin)
{
  int i=0;
#pragma omp parallel for private(i)
  for(i=0;i<fin;++i)
  {
    //prtinf("%s\n",res[i]);
  }
}