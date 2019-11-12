#include "partida.h"
#include "lista.h"
#include "arbol.h"
#include "ia.h"

#include <stdio.h>
#include <stdlib.h>

void imprimir_tablero(tPartida p){

    for(int i=0; i<3;i++){
        for(int j=0;j<3;j++){
                if((p)->tablero->grilla[i][j] ==PART_SIN_MOVIMIENTO){
                                printf(" [   ] ");
                }
                else{
                        if((p)->tablero->grilla[i][j] ==PART_JUGADOR_1){
                                printf(" [ X ] ");
                            }
                           else printf(" [ 0 ] ");
                    }
        }
        printf("\n");
    }
}
int valor_utilidad(tPartida p, int jugador){

    int ret=PART_EMPATE;
    int no_encontre_resultado=1;

     if(no_encontre_resultado==1){
     if((  p->tablero->grilla[0][0])!=PART_SIN_MOVIMIENTO){

          if (( p->tablero->grilla[0][0] ==  p->tablero->grilla[0][1] ==  p->tablero->grilla[0][2]) || ( p->tablero->grilla[0][0] == p->tablero->grilla[1][0] == p->tablero->grilla[2][0]) || (  p->tablero->grilla[0][0] == p->tablero->grilla[1][1] == p->tablero->grilla[2][2])){
                if((  p->tablero->grilla[0][0]) == jugador) {
                        //ret= PAR;
                        no_encontre_resultado=0;
                        printf("GANEE");
                }
/*
                else {
                        ret= IA_PIERDE_MAX;
                        no_encontre_resultado=0;
                     }
                     */
            }
        }
     }//fin no encontre resultado.

     if(no_encontre_resultado){

     if(( p->tablero->grilla[1][1])!=PART_SIN_MOVIMIENTO){

            if ((( p->tablero->grilla[1][0]) == ( p->tablero->grilla[1][1]) == ( p->tablero->grilla[1][2])) || (( p->tablero->grilla[0][1]) == ( p->tablero->grilla[1][1]) == ( p->tablero->grilla[2][1])) || (( p->tablero->grilla[2][0]) ==( p->tablero->grilla[1][1]) == ( p->tablero->grilla[0][2]))) {
                if(( p->tablero->grilla[1][0]) == jugador) {
                        ret= IA_GANA_MAX;
                        no_encontre_resultado=0;
                }
        /*
                else {
                        ret= IA_PIERDE_MAX;
                        no_encontre_resultado=0;
                     }
                     */
            }

        }
     }//fin no encontre resultado


     if(no_encontre_resultado){

     if(( p->tablero->grilla[2][2])!=PART_SIN_MOVIMIENTO){

        if ((( p->tablero->grilla[2][0]) == ( p->tablero->grilla[2][1]) == ( p->tablero->grilla[2][2])) || (( p->tablero->grilla[0][2]) == ( p->tablero->grilla[1][2]) == ( p->tablero->grilla[2][2]))){
                if(( p->tablero->grilla[2][0])== jugador) {
                        ret= IA_GANA_MAX;
                        no_encontre_resultado=0;
                }
                /*else {
                        ret= part;
                        no_encontre_resultado=0;
                    }
                    */

        }
     } //fin no encontre_resultado

        //CASO DE IA NO TERMINO
        if(no_encontre_resultado){
            int i=0;
            int j=0;
            while(i<2 && no_encontre_resultado==0){
                while(j<2 && no_encontre_resultado==0){
                     if ( p->tablero->grilla[i][j]!= PART_SIN_MOVIMIENTO) j=j+1;
                        else no_encontre_resultado=1; //quiere decir que IA NO TERMINO
                }
                i=i+1;
            }

            if(no_encontre_resultado==1) ret=PART_EN_JUEGO;
    }
    return ret;
}
}

int juego_modo_UvsU(tPartida p){

    int control_partida=PART_EN_JUEGO;
    int jugada_realizada;
    int x;
    int y;

    printf("\n Tablero: \n");
    imprimir_tablero(p);
    printf("\n\n Para jugar debe indicar su movimiento en terminos de fila y columna. En ese orden ");
    while(control_partida== PART_EN_JUEGO){

        if((p)->turno_de == PART_JUGADOR_1  ){
        printf("\n Turno de: %s",p->nombre_jugador_1);
         printf("\n Indique su jugada en fila: ");
         scanf("%d",&x);
         printf("Indique su jugada en columna: ");
         scanf("%d",&y);

         jugada_realizada=nuevo_movimiento(p,x,y);

         while(jugada_realizada==PART_MOVIMIENTO_ERROR){

                printf("\n Indique un valor de fila valido: ");
                scanf("%d",&x);
                printf("\n Indique un valor de columna valido: ");
                scanf("%d",&y);
                jugada_realizada=nuevo_movimiento(p,x,y);
            }
         imprimir_tablero(p);
         control_partida=valor_utilidad(p,p->turno_de);
         (p)->turno_de = PART_JUGADOR_2;

        }
    else{ // (p)->turno_de == PART_JUGADOR_2

         printf("\n Turno de: %s",p->nombre_jugador_2);
          printf("\n Indique su jugada en fila: ");
         scanf("%d",&x);
         printf("\n Indique su jugada en columna: ");
         scanf("%d",&y);

         jugada_realizada=nuevo_movimiento(p,x,y);

        while(jugada_realizada==PART_MOVIMIENTO_ERROR){
                printf("\n Indique un valor de fila valido: ");
                scanf("%d",&x);
                printf("\n Indique un valor de columna valido: ");
                scanf("%d",&y);

             jugada_realizada=nuevo_movimiento(p,x,y);

         }
         imprimir_tablero(p);
         control_partida=valor_utilidad(p,p->turno_de);
         (p)->turno_de = PART_JUGADOR_1;
        }


 }//fin while
printf("termino  %i",p->estado);
return 0;
}

int juego_modo_JyAgente(tPartida p){
    int x;
    int y;
    int jugada_realizada;
    printf("\n Tablero: \n");
    imprimir_tablero(p);
    printf("\n\n Para jugar debe indicar su movimiento en terminos de fila y columna. En ese orden \n");

    tBusquedaAdversaria b;
    int en_juego=0;
    //crear_busqueda_adversaria(&b, p);

    while(en_juego==0){

        if(p->turno_de ==PART_JUGADOR_1){
         printf("\n Turno de: %s",p->nombre_jugador_1);
         printf("\n Indique su jugada en fila: ");
         scanf("%d",&x);
         printf("\n Indique su jugada en columna: ");
         scanf("%d",&y);


         if(jugada_realizada==PART_MOVIMIENTO_ERROR){

            while(x>3 && y>3){
                printf("\n Indique un valor de fila valido: ");
                scanf("%d",&x);
                printf("\n Indique un valor de columna valido: ");
                scanf("%d",&y);
            }
         }

        jugada_realizada=nuevo_movimiento(p,x,y);
        crear_busqueda_adversaria(&b, p);
         imprimir_tablero(p);
         p->turno_de=PART_JUGADOR_2;
        }
        else //Jugador 2 AGENTE IA
        {
            proximo_movimiento(b,&x,&y);

        printf("valor x",x);
        printf("valor x \n\n",y);
         imprimir_tablero(p);
        }
    }


}

int main(){

    int modo_juego;
    int opcion_juego;
    int comienza;
    tPartida p;

    int estado_juego;

    char Jugador_1[30];
    char Jugador_2[30];

    printf("\n TA-TE-TI \n");
    printf("------------------------\n");
    printf("Opciones de partida: \n");
    printf("1 - Usuario vs Usuario: \n");
    printf("2 - Usuario vs Agente IA \n\n");
    printf("Su opcion es: ");

    scanf("%d", &modo_juego);
    if(modo_juego==1){
            printf("Indice nombre del Jugador 1: ");
            scanf("%s", Jugador_1);
            printf("Indice nombre del Jugador 2: ");
            scanf("%s", Jugador_2);
                }
    else{
            if(modo_juego==2){
            printf("Indice nombre del Jugador : ");
                  scanf("%s", Jugador_1);
                  strcpy(Jugador_2,"Agente IA");
        }
        //caso RANDOM case 3

    }
    printf("------------------------\n");
    printf("\n Indice quien comenzara la partida: \n");
    printf("1 - %s\n",Jugador_1);
    printf("2 - %s\n",Jugador_2);
    //printf("3 - Modo Aleatorio\n");
    printf("Su opcion es: ");
    scanf("%d", &opcion_juego);

    if(opcion_juego==1){
        comienza=PART_JUGADOR_1;
        }
    else comienza=PART_JUGADOR_2;

        //caso RANDOM case 3

    if(modo_juego==1) {

            //printf("\n quien comienza: ",opcion_juego);
            modo_juego= PART_MODO_USUARIO_VS_USUARIO;
            nueva_partida(&p,modo_juego,comienza,Jugador_1,Jugador_2);
            estado_juego= juego_modo_UvsU(p);
            finalizar_partida(&p);
     }
     else { nueva_partida(&p,modo_juego,comienza,Jugador_1,Jugador_2);
            modo_juego=PART_MODO_USUARIO_VS_AGENTE_IA;
            estado_juego= juego_modo_JyAgente(p);
            finalizar_partida(&p);
            }

    return 0;
}
