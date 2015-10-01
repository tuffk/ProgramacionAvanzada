#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <stdbool.h>


int factorial(int a)
	{
	int i=0; int resultado=1;
	for (i=2;i<=a; ++i)
	resultado *=i;

	return resultado;
	}
	
key_t key;
int semflg = IPC_CREAT | 0666; 
int nsems=1; 
int semid; 
int semnum;

int main()
{
    key = 1234;
    semid = semget(key, nsems, semflg);
    pid_t pid;
    pid = fork();
    while(true)
    {
        if (pid == 0)
    	 { 
    	
    		printf("%d\n",factorial(semctl(semid, semnum, GETVAL, 0)));
    		pid=1;
    	 }
    
    	else
    	{
    		int a=0;
    		printf("dame valor\n");
    		scanf("%d",&a);
    		semctl(semid, semnum, SETVAL, a); 
    		pid=0;
    		if(a==-1)
    		{
    			semctl(semid, semnum, IPC_RMID, 0); 
    			kill(pid, SIGKILL);
    		}
    	}
    }
    
    return 0;
}