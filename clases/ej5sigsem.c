#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 64
#include <signal.h>
#define FILEPATH "./mmaped.bin"
/*
void gestor_ctrlc(int sig)
{
    //printf("felicidadesp ulsaste control + c------con numero %d\n",sig);
    estado =0;
}

void gestor_ctrlz(int sig)
{
    estado=2;
}

void gestor_usr1(int sig)
{
    estado =1;
    alarm(10);
}

void gestor_alarma(int sig)
{
    estado =0;
}
*/
int main()
{
    //int kill(pid_t pid, int sig); [Option End]
    srand(time(NULL));
    
    int fd;
    int *data;
    int estado=0;
    
    
    void gestor_ctrlc(int sig)
{
    //printf("felicidadesp ulsaste control + c------con numero %d\n",sig);
    estado =0;
}

void gestor_ctrlz(int sig)
{
    estado=2;
}

void gestor_usr1(int sig)
{
    estado =1;
    printf("poniendo alarma en el semaforo %d",getpid());
    alarm(10);
}

void gestor_alarma(int sig)
{
    estado =0;
    //printf("pito\n");
    if(data[1]==(int)getpid()){
        //printf("kuz1\n");
        kill(data[2],10);
    }else if(data[2]==(int)getpid()){
        //printf("kuz1\n");
        kill(data[3],10);
    }else if (data[3]==(int)getpid()){
        //printf("kuz1\n");
        kill(data[4],10);
    }else if (data[4]==(int)getpid()){
        //printf("kuz1\n");
        kill(data[1],10);
    }
    
}
    
    
    signal(SIGALRM, gestor_alarma);

	fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);/*hacemos el archivo con flag de read y write*/
	
	data=mmap(/*(caddr_t)0*/0, 10*sizeof(int), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0);
    write(fd, "", 1);
    msync(FILEPATH, 10*sizeof(int), MS_ASYNC);
    
    if(!fork())
    {
        //sem 1
        data[1]=getpid();
		write(FILEPATH,&data,getpagesize());
		msync (FILEPATH, 10*sizeof(int), MS_ASYNC);
		signal (SIGUSR1, gestor_usr1);
		printf("p1\n");
		while(true)
		{
		    ;
		}
		exit(0);
    }
    
    if(!fork())
    {
        //sem 2
        data[2]=getpid();
		write(FILEPATH,&data,getpagesize());
		msync (FILEPATH, 10*sizeof(int), MS_ASYNC);
		signal (SIGUSR1, gestor_usr1);
		printf("hola me ejecute\n");
		while(true)
		{
		    ;
		}
		exit(0);
    }
    
    if(!fork())
    {
        //sem 3
        data[3]=getpid();
		write(FILEPATH,&data,getpagesize());
		msync (FILEPATH, 10*sizeof(int), MS_ASYNC);
		signal (SIGUSR1, gestor_usr1);
		printf("p3\n");
		
		while(true)
		{
		    ;
		}
		exit(0);
    }
    
    if(!fork())
    {
        //sem 4
        data[4]=getpid();
		write(FILEPATH,&data,getpagesize());
		msync (FILEPATH, 10*sizeof(int), MS_ASYNC);
		signal (SIGUSR1, gestor_usr1);
		printf("p4\n");
		
		while(true)
		{
		    ;
		}
		exit(0);
    }
    
    int i;
    i=kill(data[1],10);
        //printf("error: %d",i);
    sleep(30);
    munmap(data, 10*sizeof(int));
    remove(FILEPATH);
    return 0;
}