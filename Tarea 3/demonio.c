#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <stdbool.h>
#include <ctype.h>
#include <dirent.h>

void print_status(long tgid) {
    char path[40], line[100], *p;
    FILE* statusf;

    snprintf(path, 40, "/proc/%ld/status", tgid);

    statusf = fopen(path, "r");
    if(!statusf)
        return;

    while(fgets(line, 100, statusf)) {
        if(strncmp(line, "State:", 6) != 0)
            continue;
        // Ignore "State:" and whitespace
        p = line + 7;
        while(isspace(*p)) ++p;

        printf("%6d %s", tgid, p);
        break;
    }

    fclose(statusf);
}


int main (int argc, const char * argv[])
{
    pid_t pid;
    int i, c;
    int timepo=0;
    
    DIR* proc = opendir("/proc");
    struct dirent* ent;
    long tgid;
    closedir(proc);
    while ((c = getopt (argc, argv, "m:")) != -1)
        switch (c)
    {
        case 'm':
            timepo = atoi(optarg);
            //printf("valor timepo: %d\n",timepo);
            break;
        case '?':
            if (optopt == 'm')
                fprintf (stderr, "Opción -%c requiere un argumento.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Opción desconocida '-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Opción desconocida '\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
    }
    if(timepo<=0)
    {
        fprintf(stderr,"falta argumento de tiempo o no es mayor a 0");
        abort();
    }
    
    tiempo*=60;
    
    /* create new process */
    pid = fork ( );  
    if (pid == -1)  
        return -1;  
    else if (pid != 0)  
        exit (EXIT_SUCCESS);  

    /* create new session and process group */  
    if (setsid ( ) == -1)  
        return -1;  

    /* set the working directory to the root directory */  
    if (chdir (".") == -1)  
        return -1;  

    /* close all open files--NR_OPEN is overkill, but works */  
    //for (i = 0; i < NR_OPEN; i++)  
    //    close (i);  

    /* redirect fd's 0,1,2 to /dev/null */  
    //open ("/dev/null", O_RDWR);  
    /* stdin */  
    //dup (0);  
    /* stdout */  
    //dup (0);  
    /* stderror */  

    /* do its daemon thing... */  
    
    while(true)
    {
        sleep(timepo);
        proc = opendir("/proc");
        //fprintf(stderr,"soy un demonio");
        if(proc == NULL) {
        perror("opendir(/proc)");
        return 1;
        }
        
        while(ent = readdir(proc)) {
            if(!isdigit(*ent->d_name))
                continue;
    
            tgid = strtol(ent->d_name, NULL, 10);
    
            print_status(tgid);
            }

        closedir(proc);
    }

    return 0;  
}