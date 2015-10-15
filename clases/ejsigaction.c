
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void gestor(int s)
{
    printf("Se recibió la señal SIGINT\n");
}

int main(int argc, const char * argv[]) 
{
    
    struct sigaction senal;
    
    senal.sa_handler = gestor;
    senal.sa_flags = SA_ONESHOT;
    
    if ( sigaction(SIGINT, &senal, 0) == -1)
    {
        printf("Error ");
        exit(1);
    }
    
    while(1);
    
    return 0;
}