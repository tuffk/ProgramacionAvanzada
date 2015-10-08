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
#include <signal.h>

#define BUFSIZE 64
#define FILEPATH "./mmaped.bin"

int cz;
int cc;
int ymayuscula;
int segs;


int main()
{
    cc=0;
    cz=0;
    segs=3;
    pid_t id;
void gestor_ctrlc(int sig)
{
    cc++;
    ymayuscula++;
}

void gestor_ctrlz(int sig)
{
    cz++;
    if(ymayuscula>1)
        ymayuscula--;
}

void gestor_usr1(int sig)
{
    printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z. Acabando…\n",cc,cz);
    kill(id,9);
    exit(0);
}

void gestor_alarma(int sig)
{
    printf("duermo %d\n",segs);
    alarm(3);
}

signal(SIGUSR1, gestor_usr1);
signal(SIGINT,gestor_ctrlc);
signal(SIGALRM, gestor_alarma);
signal(SIGTSTP,gestor_ctrlz);
id =fork();
    if(!id)
    {
        //hijo
        sleep(10);
        kill(getppid(),10);
        
    }else
    {
        //padre
        alarm(3);
        while(true)
        {
            
        }
    }
    
    
    return 0;
}