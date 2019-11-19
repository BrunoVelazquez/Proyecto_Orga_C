#include "partida.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre)
{
    int i;
    int j;
    int opcion_juego;
    tPartida p2 = malloc(sizeof(struct partida));

    if ((p2) == NULL)
        exit(PART_ERROR_MEMORIA);

    (p2)->modo_partida= modo_partida;
    (p2)->estado= PART_EN_JUEGO;

    if (comienza==PART_JUGADOR_RANDOM)
    {
        srand(time(NULL));
        opcion_juego= rand()%2;

        if (!opcion_juego)
        {
            comienza=PART_JUGADOR_1;
        }
        else
        {
            comienza=PART_JUGADOR_2;
        }
    }

    (p2)->turno_de=comienza;

    (p2)->tablero= (tTablero) malloc(sizeof(struct tablero));

    if ((p2)->tablero == NULL)
        exit(PART_ERROR_MEMORIA);


    for (i = 0; i < 3 ; i++)
    {
        for(j = 0 ; j < 3 ; j++)
        {
            ((p2)->tablero->grilla)[i][j]=PART_SIN_MOVIMIENTO;
        }
    }

    strcpy((p2)->nombre_jugador_1,j1_nombre);
    strcpy((p2)->nombre_jugador_2,j2_nombre);
    (*p) = p2;
}


/**
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posición indicada (X,Y).
En caso de que el movimiento a dicha posición sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el número de fila, mientras Y el número de columna.
**/
int nuevo_movimiento(tPartida p, int mov_x, int mov_y)
{
    int turno_de_jugador= p->turno_de;
    printf("\nuevo mov: ES EL TURNO DE: %d",turno_de_jugador);
    int ret=PART_MOVIMIENTO_OK;
    int estado=p->estado;

    if (estado != PART_EMPATE &&
        estado != PART_GANA_JUGADOR_1 &&
        estado != PART_GANA_JUGADOR_2)
    {

        if ((mov_x-1) < 3 &&
            (mov_y-1) < 3 )
        {

            if( p->tablero->grilla[mov_x-1][mov_y-1] == PART_SIN_MOVIMIENTO)
            {
              printf("\n que hay en: %d",p->tablero->grilla[mov_x-1][mov_y-1]);
               (p->tablero->grilla)[mov_x-1][mov_y-1]=turno_de_jugador;
            }
            else
            {
                ret=PART_MOVIMIENTO_ERROR;
            }
        }
        else
        {
            ret=PART_MOVIMIENTO_ERROR;
        }
    }
    else ret= PART_MOVIMIENTO_ERROR;

    return ret;
}

/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/
void finalizar_partida(tPartida * p)
{
    (*p)->estado=-1;
    (*p)->modo_partida=-1;
    (*p)->turno_de=-1;

    free((*p)->tablero);
    (*p)=NULL;
}
