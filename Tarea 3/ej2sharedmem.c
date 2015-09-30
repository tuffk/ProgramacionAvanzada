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
#define BUFSIZE 64
#define READ 0
#define WRITE 1
#define FILEPATH "./mmaped.bin"

void fact(int* data);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    
    int fd;
    int *data;

	fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);/*hacemos el archivo con flag de read y write*/
	
	data=mmap(/*(caddr_t)0*/0, 10*sizeof(int), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED) {
	close(fd);
	perror("Error mmapping the file");
	exit(EXIT_FAILURE);
    }
	/*asignamos ale meoria a un addres que el OS escoja, el tamaño, que sea de read y write , compartida , el fd, el page size*/
    
    if (fd == -1) {
	perror("Error opening file for writing");
	exit(EXIT_FAILURE);
    }
    
    printf("file cargado y abierto correctamente \n");
    
    int result; 
    result = write(fd, "", 1);
    if (result != 1) {
	close(fd);
	perror("Error writing last byte of the file");
	exit(EXIT_FAILURE);
    }
    
    for(int KK=0;KK<10;++KK)
    {
    	data[KK*sizeof(int)] = KK;
    }
    
    msync(FILEPATH, 10*sizeof(int), MS_ASYNC);
    

    int modishnes=1;
		while(modishnes!=0)
		{
			printf("dame numero\n");
			scanf("%d",&modishnes);
			data[1]=modishnes;
			write(FILEPATH,&data,getpagesize());
			msync (FILEPATH, 10*sizeof(int), MS_ASYNC);
			if(!fork())
			{
			    fact(data);
			}
			
			wait(0);
			printf("resultado = %d\n",data[1]);
		}
		if (munmap(data, 10*sizeof(int)) == -1) {
			perror("Error un-mmapping the file");
		}
						 close(fd);
		
	return 0;
}

void fact(int* data)
{
    int zain = data[1];
    int c;
    int fact =1;
    for (c = 1; c <= zain; c++)
    {fact = fact * c;}
    data[1]=fact;
    
    write(FILEPATH,&data,getpagesize());
	msync (FILEPATH, 10*sizeof(int), MS_ASYNC);
    exit(0);
}