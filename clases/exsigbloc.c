#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

int main(int argc, const char * argv[])
{
    sigset_t bloks;
    int i;
    
    //creamos un set vacio
    sigemptyset(&bloks);
    // agregamos la señal al grupo
    sigaddset(&bloks, SIGINT);
    //blokeamos TODO lo que hay en el grupo
    sigprocmask(SIG_BLOCK, &bloks, NULL);
    ////////flag de blokeo/grp de sigs/no quiero recuperar la otra cosa
    for( i= 0; i < 10; ++i)
    {
        printf("La señal SIGINT está bloqueada ... \n");
        sleep(1);
        
    }
    printf("La señal SIGINT está por desbloquearse ... \n");
    //desbloqueamos las señales
    sigprocmask(SIG_UNBLOCK, &bloks, NULL);
    ////////flag de desblokeo/grp de sig/no me interesa cachar lo que queda
    
    while(true)
    {
        printf("estoy en un while infinito\n");
        sleep(1);
    }
    
    return 0;
}