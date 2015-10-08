#include <signal.h>
#include <stdio.h>

void gestor_ctrlc(int sig)
{
    printf("felicidadesp ulsaste control + c------con numero %d\n",sig);
}

int main()
{
    int k =10;
    if ( signal (SIGINT, gestor_ctrlc) == SIG_ERR )//cambio el comportamiento a uno definido por mi 
    {
        printf("error crenado el manejador.\n");
        exit(-1); 
    }

while ( k-- > 0) 
{ 
    printf("(%d)PID=%d. En espera de CTRL + C\n", k, getpid() );
    sleep(1); //ocasionar una espera ! 
}

k =10;
    if ( signal (SIGINT, SIG_IGN) == SIG_ERR )//cambio el comportamiento para ignorar la señal
    {
        printf("error crenado el manejador.\n");
        exit(-1); 
    }

while ( k-- > 0) 
{ 
    printf("(%d)PID=%d. En espera de CTRL + C\n", k, getpid() );
    sleep(1); //ocasionar una espera ! 
}
    
    


    k =10;
    if ( signal (SIGINT, SIG_DFL) == SIG_ERR )//regresamos el comportamiento al original 
    {
        printf("error crenado el manejador.\n");
        exit(-1); 
    }

while ( k-- > 0) 
{ 
    printf("(%d)PID=%d. En espera de CTRL + C\n", k, getpid() );
    sleep(1); //ocasionar una espera ! 
}
    
    
    
    return 0;
}