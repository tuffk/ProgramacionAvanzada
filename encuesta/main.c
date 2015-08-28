#include <stdio.h>
#include<stdlib.h>
#define M 2 //Numero de personas
#define N 7  //numero menu
#define NP 10

int i=0;
typedef struct{
	
	char *nombreP;	
	char *apellido;
	int *edad;
	
} Persona;

typedef struct{
char* pregunta;
char* r1;
char* r2;
char* r3;
char* r4;
char* r5;
char* r6;
int rusr;
}Pregunta;


typedef struct{

	Persona *participante;
	Pregunta *preguntas;
} Encuesta;




typedef void(* opcion_t) (Encuesta *, int);
typedef void(* opcion_t2) (Persona *, int);
typedef void(* opcion_t3) (Persona *, Encuesta *, int, int);


void agregarPreguntas(Encuesta *, int, int);
void jugar(Persona *,Encuesta *, int, int);
void salir(Persona *,Encuesta *, int, int);
void imprimirP(Encuesta *, int, int);


int main(int argc, const char * argv[])
{
    
}//Cierre de main


void agregarPreguntas(Encuesta *e, int a, int b)
{
    e->preguntas=(Pregunta*)malloc(NP*sizeof(Pregunta));
    int i=0;
    Pregunta* aux = e->preguntas;
    for(;i<NP;++i)
    {
        printf("dame la pregunta %d",i);
        (aux+i)->pregunta = (char*)malloc(sizeof(char)*40);
        scanf("%s", (aux+i)->pregunta);
        
        printf("dame la respuesta 1");
        (aux+i)->r1 = (char*)malloc(sizeof(char)*40);
        scanf("%s", (aux+i)->r1);
        
        printf("dame la respuesta 2");
        (aux+i)->r1 = (char*)malloc(sizeof(char)*40);
        scanf("%s", (aux+i)->r2);
        
        printf("dame la respuesta 3");
        (aux+i)->r1 = (char*)malloc(sizeof(char)*40);
        scanf("%s", (aux+i)->r3);
        
        printf("dame la respuesta 4");
        (aux+i)->r1 = (char*)malloc(sizeof(char)*40);
        scanf("%s", (aux+i)->r4);
        
        printf("dame la respuesta 5");
        (aux+i)->r1 = (char*)malloc(sizeof(char)*40);
        scanf("%s", (aux+i)->r5);
        
        printf("dame la respuesta 6");
        (aux+i)->r1 = (char*)malloc(sizeof(char)*40);
        scanf("%s", (aux+i)->r6);
    }
	
}//cierre de agrega preguntas



void jugar(Persona *p, Encuesta *e, int a, int b)
{

}//Cierre de funcion jugar



void imprimirP(Encuesta *e, int a, int b)
{
    

}//Cierre de imprimirP



void salir(Persona *p, Encuesta *e, int a, int b)
{

}//Cierre de funcion salir
