#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#define suxname "sux"
/*
primero correr el servidor (ej5s.c)
para que el socket funcione
*/

int main(int argc, const char * argv[]) {
    
    
    
    struct sockaddr_un direccion;
    char buffer[1000];

    
    int cliente;
    
    int leidos, escritos;
   
    //Crear el socket
    cliente = socket(PF_LOCAL, SOCK_STREAM, 0);
    
    // Establecer conexión
    direccion.sun_family = AF_LOCAL;
    strcpy(direccion.sun_path,suxname);
    
    int estado = connect(cliente,&direccion, SUN_LEN(&direccion));
    // Comunicación
    
    if (estado == 0) {

        while (leidos = read(fileno(stdin), &buffer, sizeof(buffer))) {

            write(cliente, &buffer, leidos);
            leidos = read(cliente, &buffer, sizeof(buffer));
            write(fileno(stdout), &buffer, leidos);
        }
    }
    
    // Cerrar el socket
    close(cliente);
    
    return 0;
}