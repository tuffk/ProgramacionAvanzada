#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#define N 10
#define M 10
#define NULL (void*)0

/*
el formato de las fechas (para facilitar busquedas y comparaciones) es de enteros
con el año luego el mes y luego el dia de la siguiente forma añoMesDia
por ejemplo
19930305 es 1993- 03 - 05 marzo 5 del 93
20000109 9 enero del 2000
favor de tomar nota de lo anterior
*/


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
  int *periodo;
  int *pisos;
}Edificio;

typedef struct{
    int *modales;
    int periodo;
    int* dSuperior;
    int* dInferior;
    int pisos;
}Torre;

typedef struct{
    int modales;
    int periodo;
    char* techo;
    int pisos;
}Nave;

typedef struct{
    int fecha;
    Nave* nave;
    Torre* torre;
    Nave* edificio;
    Persona * constructor;
    int type;
}Modelo;

typedef void(*func)(Persona*);

void addNomina(Persona*,int);
void delNomina(Persona*,int);
void construir(Modelo*,Persona*,int);
void printByDate(Modelo*,Persona*,int,int, int);
void printrh(int,int,Modelo*,Persona*,int);
void edit(Persona*, int);
int tampP(Persona*);
int tamM(Modelo*);
void del(Persona*,int,Modelo*,int);


int main(){
    
    Persona* RH = (Persona*)malloc(N*sizeof(Persona));
    Modelo* modelos = (Modelo*)malloc(M*sizeof(Modelo));

    int opcion=-1;
    int id=0;
    int fec=0;
    int zrh=0;
    int zmod=0;
    while(opcion !=0){
    printf("que quieres\nagregar empleado -1\neliminar empleado - 2\nhacer un modelo -3\nver por fecha -4\nver nomina -5\n salir - 0 \n");
    scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                //printf("agregando");
                addNomina(RH,zrh);
                zrh++;
                //printf("agregado");
            break;
            case 2:
                delNomina(RH,zrh);
                zrh--;
            break; 
            case 3:
                construir(modelos,RH,zmod);
                zmod++;
            break;
            case 4:
            printf("log in para poder ver tus modelos(osea tu numero de nomina)");
            scanf("%d",&id);
            printf("en que fehca deseas buscar? formato 19930317");
            scanf("%d",&fec);
            printByDate(modelos,RH, fec,id, zmod);
            break;
            case 5:
                printrh(1,3,modelos,RH,zmod);
                //printf("edificio %d pisps \n",(modelos->edificio->pisos));
            break;
            default: printf("error\n"); break;
        }
    }
    
    edit(RH,zrh);
    
    if(!fork())
    {
        //hijo
        printf("log in para poder ver tus modelos(osea tu numero de nomina)\n");
            scanf("%d",&id);
            printf("en que fehca deseas buscar? formato 19930317\n");
            scanf("%d",&fec);
            printByDate(modelos,RH, fec,id, zmod);
        
        exit(0);//matando al hijo
    }
    else
    {
        //padre
        wait(0);//dado que solo tengo 1 consola para probarlo pues tiene que ser "paralelo" uno tras otro 
        
        printf("log in para poder ver tus modelos(osea tu numero de nomina)\n");
            scanf("%d",&id);
            printf("en que fehca deseas buscar? formato 19930317\n");
            scanf("%d",&fec);
            printByDate(modelos,RH, fec,id, zmod);
    }
//    del(RH,zrh,modelos,zmod);
    free(RH);
    free(modelos);
    return 0;
}

int tampP(Persona*lista){
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

void edit(Persona* ls, int c)
{
    Persona* aux=ls;
    int id;
    printf("dame tu id\n");
    scanf("%d",&id);
    int i =0;
    while(i < c)
    {
        if((aux+i)->nomina == id)
        {
            (aux+id)->nombre = "new";
            (aux+id)->nombre = "another";
            (aux+id)->salario = 88;
        }
        i++;
    }
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
            printf("torre 1, nave 2, edificio 3\n");
            scanf("%d",&i);
            switch(i)
            {
                case 1:

                printf("numero de tpisos\n");
                scanf("%d",&i);
                Torre* temp=(Torre*)malloc(sizeof(Torre));
                temp->modales=(int*) malloc(i*sizeof(int));
                temp->periodo =8;
                temp->dSuperior=(int*) malloc(i*sizeof(int));
                temp->dInferior=(int*) malloc(i*sizeof(int));
                
                temp->pisos=i;
                (((mls+c)->torre)) = temp;
                (((mls+c)->type)) = 1;
                break;
                case 2:
                 printf("numero de pisos\n");
                scanf("%d",&i);
                Nave* temp2=(Nave*)malloc(sizeof(Nave));
                //temp2->modales=(int*) malloc(i*sizeof(int)); // es 1 asi q no es nesesario malloc
                temp2->periodo =8;
                temp2->techo = "aguas";
               
                temp2->pisos=1;
                (((mls+c)->nave)) = temp2;
                (((mls+c)->type)) = 2;
                break;
                
                case 3:
                printf("numero de episos\n");
                scanf("%d",&i);
                Edificio* temp3=(Edificio*)malloc(sizeof(Edificio));
                temp3->modales=(int*) malloc(i*sizeof(int));
                temp3->periodo =8;
                temp3->simetrico = true;
          
                temp3->pisos=i;
                (((mls+c)->edificio)) = temp3;
                (((mls+c)->type)) = 3;
                //printf("%d\n",(((mls+c)->edificio)->pisos));
                break;
            }
            return;
        }
        
    }
}

void printrh(int a,int b,Modelo*mls,Persona* ls,int c)
{
    Modelo*aux;
    Persona* aux2;
    int i =0;
    int dia=a;
    int tot=0;
    aux2=ls;
    aux=mls;
    while(i < c)
    {
        if(aux->fecha <b && aux->fecha >a)
        {
            printf("trabajo realizado por: %s \n",(aux->constructor->nombre));
            printf("su puesto es %s \n",(aux->constructor->puesto));
            if(aux->type ==1)
            {
                printf("una torre de : %d pisos\n", aux->torre->pisos);
            }else if(aux->type ==2){
                printf("una nave de : 1 pisos\n");
            }else if(aux->type ==3){
                printf("un edificio de : %d pisos\n", aux->edificio->pisos);
            }
            tot++;
            
        }
        i++;
        dia++;
        printf("total de modelso contruidos el dia %d: %d \n",dia,tot);
        if(i<c)
        {aux++;}
        
    }
    
}


void printByDate(Modelo* mls,Persona* ls,int fechasss,int id, int c)
{
    Modelo* aux = mls;
    Persona* aux2 = ls;
    int i =0;
    while(i < c)
    {
        if(aux->fecha == fechasss && aux->constructor->nomina == id)
        {
            if(aux->type ==1)
            {
                printf("una torre de : %d pisos\n", aux->torre->pisos);
            }else if(aux->type ==2){
                printf("una torre de : 1 pisos\n");
            }else if(aux->type ==3){
                printf("una torre de : %d pisos\n", aux->edificio->pisos);
            }
        }
        i++;
       if(i<c)
        {aux++;} 
    }
}


void del(Persona* ls,int tamls,Modelo* mls,int tamods)
{
    int i;
    Persona*aux=ls;
    Modelo* aux2=mls;
    for(i=0;i<tamls;i++)
    {
        free(*((aux+i)->nombre));
        free(*((aux+i)->apellido));
        free(*((aux+i)->puesto));
        printf("hola -%d-",i);
    }
    
    for(i=0;i<tamods;i++)
    {
        free((aux2+i)->constructor);
        if((aux2+i)->type ==1)
            {
               free((aux2+i)->torre);
            }else if((aux2+i)->type ==2){
                free((aux2+i)->nave);
            }else if((aux2+i)->type ==3){
                free((aux2+i)->edificio);
            }
            printf("adios -%d-",i);
    }
}