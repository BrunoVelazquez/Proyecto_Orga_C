#include <stdio.h>

#include "partida.h"
#include "lista.h"
#include "arbol.h"
#include "ia.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int valor_utilidad(tEstado e, int jugador_max)
{
    int ret=IA_EMPATA_MAX;
    int no_encontre_resultado=1;
    printf("adentro de f");
    if(no_encontre_resultado==1){

     if(( e->grilla[0][0])!=108){



          if (((e->grilla[0][0] == jugador_max) && (e->grilla[0][1] == jugador_max) && ( e->grilla[0][2] == jugador_max)) ||
              ((e->grilla[0][0] == jugador_max) && (e->grilla[1][0] == jugador_max) && ( e->grilla[2][0] == jugador_max)) ||
              ((e->grilla[0][0] == jugador_max) && (e->grilla[1][1] == jugador_max) && ( e->grilla[2][2] == jugador_max))){

                if(( e->grilla[0][0]) == jugador_max) {
                        ret= IA_GANA_MAX;
                        printf("\n entre  a este if 1");
                        no_encontre_resultado=0;
                }
                  else
                      {
                                ret= IA_PIERDE_MAX;
                                printf("\n entre a IA PIERDE MAX");
                                no_encontre_resultado=0;
                }
            }
        }


     }//fin no encontre resultado.

     if(no_encontre_resultado==1){

     if((e->grilla[1][1])!=108){

        if(   ((e->grilla[1][0] == jugador_max) && (e->grilla[1][1]==jugador_max) && (e->grilla[1][2] ==jugador_max)) ||
              (( e->grilla[0][1] == jugador_max) && (e->grilla[1][1]== jugador_max) && ( e->grilla[2][1]==jugador_max)) ||
              ((e->grilla[2][0] == jugador_max) && (e->grilla[1][1]==jugador_max) && ( e->grilla[0][2]== jugador_max))){
                if((e->grilla[1][1]) == jugador_max) {
                        ret= IA_GANA_MAX;
                         printf("\n entre  a este if 2");
                        no_encontre_resultado=0;
                }

                else
                {
                  ret= IA_PIERDE_MAX;
                  printf("\n entre a IA PIERDE MAX");
                 no_encontre_resultado=0;
                }
            }
        }


     }//fin no encontre resultado


     if(no_encontre_resultado==1){

     if((e->grilla[2][2])!=108){

        if (  ((e->grilla[2][0] == jugador_max) && (e->grilla[2][1]==jugador_max) && (e->grilla[2][2] ==jugador_max)) ||
              (( e->grilla[0][2] == jugador_max) && (e->grilla[1][2]== jugador_max) && ( e->grilla[2][2]==jugador_max)) ){
                if((e->grilla[2][2])== jugador_max) {
                        ret= IA_GANA_MAX;
                         printf("\n entre  a este if 3");
                        no_encontre_resultado=0;
                }
                  else
                {
                                  printf("\n entre a IA PIERDE MAX");
                                    ret= IA_PIERDE_MAX;
                               no_encontre_resultado=0;
                }
            }
        }


    } //fin no encontre_resultado

        //CASO DE IA NO TERMINO
    if (no_encontre_resultado==1)
    {
        int i=0;
        int j=0;
        while ( i < 3 && no_encontre_resultado==1 )
        {
            while( j < 3 && no_encontre_resultado==1 )
            {
                if (e->grilla[i][j]!= 108)
                {
                    j=j+1;
                }
                else
                {
                    no_encontre_resultado=0; //quiere decir que IA NO TERMINO
                }
            }
            j=0;
            i=i+1;
        }
        if (no_encontre_resultado==0)
        {
            ret=IA_NO_TERMINO;
        }
    }
   // printf("\n RET DE VALOR UTILIDAD: %d \n",ret);
    //printf("  con ficha: %d",jugador_max);
    return ret;
}

int main()
{
    tEstado e;
    //int grilla[3][3];
e = (tEstado) malloc(sizeof(struct estado));

    if (e == NULL)
        exit(IA_ERROR_MEMORIA);
    for (int i = 0; i < 3 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            e->grilla[i][j]=108;
            printf("aca");
        }
    }
    //printf("aca");
    e->grilla[0][0]=101;
    e->grilla[0][1]=101;
    e->grilla[0][2]=101;
    e->grilla[1][1]=100;
    e->grilla[1][2]=100;
    e->grilla[2][1]=100;

    printf("la utilidad: %d",valor_utilidad(e,100));


return 0;




}
