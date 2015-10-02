#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define suxname "sux"

/*
sugerencia para correrlo
pasar como argumento el socket sux
ejemplo
./elarchivo sux
de lo contrario favor de eliminar el archivo manualmente
*/

int main(int argc, const char * argv[]) {
    
    
    remove("./sux");
    
    struct sockaddr_un direccion;
    char buffer[1000];
    
    int servidor, cliente;
    
    int leidos, escritos;
    
    
    servidor = socket(PF_LOCAL, SOCK_STREAM, 0);
    
    direccion.sun_family = AF_LOCAL;
    strcpy(direccion.sun_path,suxname);
    
    bind(servidor,&direccion, SUN_LEN(&direccion));
    
    // Escuchar a los clientes
    listen(servidor, 10);
    
    // Comunicación
    socklen_t tamano = sizeof(direccion);
    
    cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
    
    if (cliente >= 0) {
        
        while (leidos = read(cliente, &buffer, sizeof(buffer))) {
            write(fileno(stdout), &buffer, leidos);
            leidos = read(fileno(stdin), &buffer, sizeof(buffer));
            write(cliente, &buffer, leidos);
        }     
    }
    
    // Cerrar el socket
    close(servidor);
    close(cliente);
    
    return 0;
}