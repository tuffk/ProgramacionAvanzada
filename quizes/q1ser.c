
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TCP_PORT 8000
int *nums;

int main(int argc, const char * argv[]) {
    
    srand((int)time(NULL));
    
    struct sockaddr_in direccion;
    char buffer[1000];
    
    int servidor, cliente;
    
    int* leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    //servidor = socket(PF_UNIX, SOCK_STREAM, 0);
    
    // Enlace con el socket
    direccion.sin_port = htons(TCP_PORT);//eliminar esto si se usa UNIX
    direccion.sin_family = AF_INET;
    //direccion.sin_family = AF_UNIX;
    inet_aton(argv[1], &direccion.sin_addr);//eliminar esto si se usa UNIX
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Escuchar a los clientes
    listen(servidor, 10);
    
    // Comunicación
    socklen_t tamano = sizeof(direccion);
    while(true)
    {
        cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
        if(!fork())
            break;
    }
    
    close(servidor);
    int i =0;
    int r = rand()%1000;
    if (cliente >= 0) {
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        // Leer de socket y escribir en pantalla
        while (/*leidos = read(cliente, &buffer, sizeof(buffer))*/1) {
            //write(fileno(stdout), &buffer, leidos);
            r=rand()%100;
            nums=(int*)malloc(r*sizeof(int));
            for(i=0;i<r;i++)
            {
                *(nums+i)=rand();
            }
            leidos = nums;
            //leidos = read(fileno(stdin), &buffer, sizeof(buffer));
            write(cliente, &buffer, leidos);
            
        }
        
        
    }
    
    // Cerrar el socket
    
    //close(servidor);
    close(cliente);
    
    return 0;
}