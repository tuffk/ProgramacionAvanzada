/*
robot
3 a la derecha
2 hacia abajo 
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>

bool valida(int n, int m)
{
    if(n%3 !=0)
        return false;
    if(m%2 != 0)
        return false;
    return true;
}

int main()
{
    int n, m;
    n = m = 0;
    printf("dame n y m para el tablero\n");
    scanf("%d%d",&n,&m);
    printf("n:%d---m:%d",n,m);
    if(!valida(m,n)){
        printf("tablero sin solucion\n");
        return 0;}
    int M[m][n];
    int posx, posy;
    posx = posy = 0;
    #pragma omp parallel private(posx,posy)
    {
        #pragma sections
        {
            #pragma sections
            {
                for(int i =0; i <(n/3);++i)
                {
                    if((posx+3)<=n)
                    {
                        printf("d,");
                        posx+=3;
                    }else{
                        printf("a,");
                        posy+=3;
                    }
                    printf("\n");
                }
            }
            
            
            
        }
        
    }
    
    return 0;
}