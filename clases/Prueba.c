#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

int main(int argc, const char * argv[])
{
    sigset_t bloks, recups;
    int i;
    
    sigemptyset(&bloks);
    
    sigaddset(&bloks,SIGINT);
    sigaddset(&bloks,SIGTSTP);
    sigaddset(&bloks, SIGUSR1);
    
    sigprocmask(SIG_BLOCK, &bloks, NULL);
    
    while(true)
    {
        i++;
        printf("%d",i);
        sleep(1);
        if(i>10)
        break;
    }
    
    sigprocmask(SIG_UNBLOCK, &bloks, &recups);
    printf("pito\n");
    
    return 0;
}