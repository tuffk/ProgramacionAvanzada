#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#define SIGALARM 14

int grabar;

int main(int argc, const char * argv[])
{
    struct dirent* ent;
    sigset_t ninguna, todas;
    grabar=1;
    
    sigemptyset(&ninguna);
    sigfillset(&todas);
    
    sigdelset(&todas, SIGALARM);
    
    sigprocmask(SIG_BLOCK, &todas, NULL);
    
    mkdir("./datos", S_IRWXU|S_IRWXG|S_IRWXO);
    DIR* proc = opendir("./datos");
    FILE * file;
    int fd =3;
    char pathFile = "./datos";
    while(ent = readdir(proc)) {
            
            sprintf(pathFile, "%s\\my_log.txt", "datos" );
            int filedescriptor = open(pathFile, O_RDWR | O_APPEND | O_CREAT);  
            write(filedescriptor,"x",(sizeof(char)));
            }
sigprocmask(SIG_UNBLOCK, &todas, NULL);
    
        closedir(proc);
    
   /* struct stat s;
int err = stat("./datos", &s);
if(-1 == err) {
    if(ENOENT == errno) {
        system("mkdir ./datos");
    } else {
        perror("stat");
        exit(1);
    }
} else {
    if(S_ISDIR(s.st_mode)) {
        printf("ya existe");
    } else {
        printf("existe un archivo del mismo nombre y no es un direcotrio");
    }
}*/
    
    return 0;
}