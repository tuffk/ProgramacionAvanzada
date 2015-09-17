#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#define N 10
#define M 10
#define NULL (void*)0

typedef struct{
    int nomina;
    char* nombre;
    char * apellido;
    int nacimiento;
    int ingreso;
    int salario;
    char* puesto;
}Persona;

typedef struct{
  int *modales;
  bool simetrico;
  int periodo;
}Edificio;

typedef struct{
    int *modales;
    int periodo;
    int* dSuperior;
    int* dInferior;
}Torre;

typedef struct{
    int modales;
    int periodo;
    char* techo;
}Nave;

typedef struct{
    int fecha;
    Nave* nave;
    Torre torre;
    Nave* edificio;
    Persona * constructor;
}Modelo;

typedef void(*func)(Persona*);

void addNomina(Persona*);
void delNomina(Persona, Persona*);
void construir(Persona, Modelo*);
void printByDate(Modelo*,int);
void printrh(int,int,Persona,Modelo*);
int tampP(Persona*);
int tamM(Modelo*);

int main(){
    
    Persona* RH = (Persona*)malloc(N*sizeof(Persona));
    Modelo* modelos = (Modelo*)malloc(M*sizeof(Modelo));
    modelos=NULL;
    int opcion=-1;
    while(opcion !=0){
    printf("que quieres\nagregar empleado -1\neliminar empleado - 2\nhacer un modelo -3\nver por fecha -4\nver nomina -5\n salir - 0 \n");
    scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
            printf("agregando");
                addNomina(RH);
                printf("agregado");
            break;
            default: printf("error"); break;
        }
    }
    free(RH);
    free(modelos);
    return 0;
}

int tampP(Persona*lista)
{
    int t=0;
    Persona*aux;
    aux = lista;
    while(aux !="\0")
    {
        t++;
        aux++;
    }
    return t;
}
int tamM(Modelo*lista){
    int t=0;
    Modelo*aux;
    aux = lista;
    while(aux !="\0")
    {
        t++;
        aux++;
    }
    return t;
}

void addNomina(Persona* lista){
    int tam = tampP(lista);
    if(tam>N)
    {
        lista = (Persona*)realloc(lista,(N+10)*sizeof(Persona));
    }
    char* nom=(char*)malloc(30*sizeof(char));
    printf("dame nombre");
    scanf("%s",&nom);
    Persona* temp=(Persona*)malloc(sizeof(Persona));

    (temp)->nomina =1;
    (temp)->nombre =(char*)malloc(30*sizeof(char));
    (temp)->nombre =nom;
    (temp)->apellido = "perez";
    (temp)->ingreso = 20000103;
    (temp)->salario = 500;
    (temp)->nacimiento = 1984023;
    (temp)->puesto = "puesto";
    *(lista+tam)=*temp;
}