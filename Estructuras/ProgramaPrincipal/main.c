#define MAIN_PRINCIPAL

#include "partida.h"
#include "lista.h"
#include "arbol.h"
#include "ia.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef MAIN_PRINCIPAL

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

void solicitar_movimiento(tPartida p){

    int x;
    int y;
    int jugada_realizada;
    int turno= p->turno_de;

        if(turno==PART_JUGADOR_1){
            printf("\n\n\n Turno de: %s",p->nombre_jugador_1);
        }
        else {
                printf("\n\n\n Turno de: %s",p->nombre_jugador_2);
             }

    printf("\nIndique su jugada en fila: ");
    scanf("%d",&x);
    printf("Indique su jugada en columna: ");
    scanf("%d",&y);

    jugada_realizada=nuevo_movimiento(p,x,y);

    while(jugada_realizada==PART_MOVIMIENTO_ERROR){

        printf("\n Indique un valor de fila valido: ");
        scanf("%d",&x);
        printf("Indique un valor de columna valido: ");
        scanf("%d",&y);
        jugada_realizada=nuevo_movimiento(p,x,y);
    }
}

int resultado_partida(tPartida p,int jugador){

int retornar=0;


int no_encontre_resultado=1;
printf("\n\n print no encontre resultado %d",&no_encontre_resultado);

if(no_encontre_resultado==1){

	if(p->tablero->grilla[0][0]!= PART_SIN_MOVIMIENTO){

		if( (p->tablero->grilla[0][0] == p->tablero->grilla[0][1] == p->tablero->grilla[0][2]) || (p->tablero->grilla[0][0] == p->tablero->grilla[1][0] == p->tablero->grilla[2][0]) || (p->tablero->grilla[0][0] == p->tablero->grilla[1][1] == p->tablero->grilla[2][2]) ) {
			if( p->tablero->grilla[0][0] == jugador) {
				retornar=1;
				no_encontre_resultado=0;
				}
			}
		}
}

if(no_encontre_resultado==1){

	if(p->tablero->grilla[1][1]!= PART_SIN_MOVIMIENTO){

		if( (p->tablero->grilla[1][0] == p->tablero->grilla[1][1] == p->tablero->grilla[1][2]) || (p->tablero->grilla[0][1] == p->tablero->grilla[1][1] == p->tablero->grilla[2][1]) || (p->tablero->grilla[2][0] == p->tablero->grilla[1][1] == p->tablero->grilla[0][2]) ) {
			if( p->tablero->grilla[1][0] == jugador) {
				retornar=1;
				no_encontre_resultado=0;
				}
			}
		}
}

if(no_encontre_resultado==1){

	if(p->tablero->grilla[2][2]!= PART_SIN_MOVIMIENTO){

		if( (p->tablero->grilla[2][0] == p->tablero->grilla[2][1] == p->tablero->grilla[2][2]) || (p->tablero->grilla[0][2] == p->tablero->grilla[1][2] == p->tablero->grilla[2][2]) ) {
			if( p->tablero->grilla[2][0] == jugador) {
				retornar=1;
				no_encontre_resultado=0;
				}
			}
		}
}
printf("el retorno %d",&retornar);
return retornar;

}

int juego_modo_UvsU(tPartida p){

    int control_partida=PART_EN_JUEGO;

    printf("\n Tablero: \n");
    imprimir_tablero(p);
    printf("\n\n Para jugar debe indicar su movimiento en terminos de fila y columna. En ese orden ");
    while(control_partida== PART_EN_JUEGO){

        if((p)->turno_de == PART_JUGADOR_1  ){

            solicitar_movimiento(p);
            imprimir_tablero(p);

            int i= resultado_partida(p,p->turno_de);

            printf("resultado de metodo resultado %d",&i);
             if(i==1){
                    printf("adentro if");
                control_partida= PART_GANA_JUGADOR_1;
             }
             else control_partida= PART_EMPATE;

                    (p)->turno_de = PART_JUGADOR_2;

            }
        else{ // (p)->turno_de == PART_JUGADOR_2
                solicitar_movimiento(p);
                imprimir_tablero(p);

                if(resultado_partida(p,p->turno_de)==1){
                        printf("adentro if");
                control_partida= PART_GANA_JUGADOR_2;
                }
                else control_partida= PART_EMPATE;

                (p)->turno_de = PART_JUGADOR_1;

            }


        }//fin while
        printf("Control partida %d",&control_partida);
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
            solicitar_movimiento(p);

            crear_busqueda_adversaria(&b, p);
            printf("luego de crear adversario");
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

    }
    printf("------------------------\n");
    printf("\n Indice quien comenzara la partida: \n");
    printf("1 - %s\n",Jugador_1);
    printf("2 - %s\n",Jugador_2);
    printf("3 - Modo Aleatorio\n");
    printf("Su opcion es: ");
    scanf("%d", &opcion_juego);

    if(opcion_juego==1){
        comienza=PART_JUGADOR_1;
        }
    else {
            if(opcion_juego==2){
            comienza=PART_JUGADOR_2;
            }
            else { comienza= PART_JUGADOR_RANDOM;
                 }
    }


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

#endif // MAIN_PRINCIPAL
