#include <signal.h>
#include <stdio.h>

void gestor_ctrlc(int sig)
{
    //printf("felicidadesp ulsaste control + c------con numero %d\n",sig);
    
}

void gestor_ctrlc2(int sig)
{
    //printf("felicidadesp ulsaste control + c------con numero %d\n",sig);
    printf("solo muere mi hijo\n");
}

void gestor_ctrlz(int sig)
{
    printf("dice cubells que nadie peude detenerlo");
}

int main()
{
    
    if ( signal (SIGTSTP, gestor_ctrlz) == SIG_ERR )//cambio el comportamiento para ignorar la señal
    {
        printf("error crenado el manejador.\n");
        exit(-1); 
    }
    pid_t pid = fork();
    if(!pid)
    {
        sleep(2);
        //hijo
        printf("soy el hijo y mi pid: %d\t y el de mi papa: %d",pid,getppid());
        if ( signal (SIGINT, gestor_ctrlc) == SIG_ERR )//cambio el comportamiento para ignorar la señal
    {
        printf("error crenado el manejador.\n");
        exit(-1); 
    }
    int i=0;
    for(;i<10;++i)
    {
        sleep(1);
        printf("%d\n",i);
    }
        
    }
    else
    {
        //padre
        printf("soy el papa y mi pid: %d\n",getpid());
        if ( signal (SIGINT, gestor_ctrlc2) == SIG_ERR )//cambio el comportamiento para ignorar la señal
        {
        printf("error crenado el manejador.\n");
        exit(-1); 
         }
        
    }
    
    return 0;
}