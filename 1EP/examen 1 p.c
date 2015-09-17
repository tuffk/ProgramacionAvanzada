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
    Torre* torre;
    Nave* edificio;
    Persona * constructor;
}Modelo;

typedef void(*func)(Persona*);

void addNomina(Persona*,int);
void delNomina(Persona*,int);
void construir(Modelo*,Persona*,int);
void printByDate(Modelo*,int,int);
void printrh(int,int,Persona,Modelo*,int);
int tampP(Persona*);
int tamM(Modelo*);

int main(){
    
    Persona* RH = (Persona*)malloc(N*sizeof(Persona));
    Modelo* modelos = (Modelo*)malloc(M*sizeof(Modelo));

    int opcion=-1;
    int zrh=0;
    int zmod=0;
    while(opcion !=0){
    printf("que quieres\nagregar empleado -1\neliminar empleado - 2\nhacer un modelo -3\nver por fecha -4\nver nomina -5\n salir - 0 \n");
    scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
            printf("agregando");
                addNomina(RH,zrh);
                zrh++;
                printf("agregado");
            break;
            case 2:
                delNomina(RH,zrh);
                zrh--;
            break; 
            case 3:
                construir(modelos,RH,zmod);
                zmod++;
            break;
            default: printf("error\n"); break;
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

void addNomina(Persona* p,int c){

    if(c>N)
    {
        p = (Persona*)realloc(p,(N+10)*sizeof(Persona));
    }
    printf("Dame el numero de nomina: ");
	scanf("%d",(&(p+c)->nomina));
	(p+c)->nombre = malloc(sizeof(char)*10); 
	//printf("Dame el nombre: ");
	//scanf("%s",(p+c)->nombre);
	(p+c)->nombre = "hola";
	(p+c)->apellido = malloc(sizeof(char)*10);
	//printf("Dame el apellido: ");
	//scanf("%s",(p+c)->apellido);	
    (p+c)->apellido="adios";
	
	//printf("Dame la fecha nacimiento en este formato ejemplo 19490103 :  ");
	//scanf("%d",(&(p+c)->nacimiento));  
(p+c)->nacimiento=1;
	//printf("Dame la fecha de Ingreso en este formato ejemplo 19991111 :  ");
	//scanf("%d",(&(p+c)->ingreso));
	(p+c)->ingreso=1;

	//printf("Dame el salario: ");
	//scanf("%d",(&(p+c)->salario));
	(p+c)->salario=1;
	(p+c)->puesto = malloc(sizeof(char)*10);
	//printf("Dame el puesto: ");
	//scanf("%s",(p+c)->puesto);	
	(p+c)->puesto="violador";
}

void delNomina(Persona* lista,int c)
{
    printf("a quien quieres correr?(numero de nomina)\n");
    int id=0;
    scanf("%d",&id);
    Persona*aux;
    Persona*aux2;
    aux2 =(lista+c);
    aux = lista;
    while((aux) !="\0")
    {
        aux++;
        if((aux)->nomina ==id)
        {
            //free(aux);
            aux=aux2;
            printf("corrido exitosamente");
            return;
        }
        
    }
    
    printf("no encontre a quien correr");
}

void construir( Modelo* mls,Persona * ls,int c)
{
    printf("a quien quieres asignar este proyecto?(numero de nomina)\n");
    int id=0;
    scanf("%d",&id);
    Persona*aux;
    aux = ls;
    if(c>M)
    {
        mls=(Modelo*)realloc(mls,(sizeof(Modelo)*M+10));
    }
int i=0;
int x=0;
    while((aux) !="\0")
    {
        aux++;
        if((aux)->nomina ==id)
        {
            (mls+c)->constructor = aux;
            (mls+c)->fecha = 2;
            printf("torre 1, nave 2, edificio 3");
            scanf("%d",&i);
            switch(i)
            {
                case 1:

                printf("numero de pisos");
                scanf("%d",&i);
                Torre* temp=(Torre*)malloc(sizeof(Torre));
                temp->modales=(int*) malloc(i*sizeof(int));
                temp->periodo =8;
                temp->dSuperior=1;
                temp->dInferior=1;
                (((mls+c)->torre)) = temp;
                break;
                case 2:
                 printf("numero de pisos");
                scanf("%d",&i);
                Nave* temp2=(Nave*)malloc(sizeof(Nave));
                //temp2->modales=(int*) malloc(i*sizeof(int));
                temp2->periodo =8;
                temp2->techo = "aguas";
                (((mls+c)->nave)) = temp2;
                break;
                
                case 3:
                printf("numero de pisos");
                scanf("%d",&i);
                Edificio* temp3=(Edificio*)malloc(sizeof(Edificio));
                temp3->modales=(int*) malloc(i*sizeof(int));
                temp3->periodo =8;
                temp3->simetrico = true;
                (((mls+c)->torre)) = temp;
                break;
            }
            return;
        }
        
    }
}