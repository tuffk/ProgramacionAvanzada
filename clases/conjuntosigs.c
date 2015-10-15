#include <stdio.h>
#include <signal.h>

int main(int argc, const char * argv[])
{
    
    sigset_t ninguna, todas;
    
    sigemptyset(&ninguna);
    sigfillset(&todas);
    
    sigaddset(&ninguna, SIGINT);//agregar una señal al conjunto
    
    
    if (sigismember(&ninguna, SIGINT))// revisar si una señal esta en un grupo
        printf("SIGINT pertenece al conjunto ninguna\n");
    else
        printf("SIGINT no pertenece al conjunto ninguna \n");
    
    sigdelset(&todas, SIGINT);//borrar / sacar la señal del grupo 
    
    if (sigismember(&todas, SIGINT))
        printf("SIGINT pertenece al conjunto todas \n");
    else
        printf("SIGINT no pertenece al conjunto todas \n");
    
    return 0;
}