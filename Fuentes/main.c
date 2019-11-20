#define MAIN_PRINCIPAL

#include "partida.h"
#include "lista.h"
#include "arbol.h"
#include "ia.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef MAIN_PRINCIPAL

static int seleccionar_modo_de_juego();
static void indicar_nombres( char* jugador_1, char* jugador_2 , int modo_juego);
static int seleccionar_quien_comienza(int* opcion, char * jugador_1 , char* jugador_2);
static int seguir_jugando();

void imprimir_tablero(tPartida p)
{
    for ( int i = 0 ; i < 3 ; i++ )
    {
        for ( int j = 0 ; j < 3; j++ )
        {
            switch ((p)->tablero->grilla[i][j])
            {
                case PART_SIN_MOVIMIENTO:
                    printf(" [   ] ");
                    break;
                case PART_JUGADOR_1:
                    printf(" [ X ] ");
                    break;
                case PART_JUGADOR_2:
                    printf(" [ 0 ] ");
                    break;
            }
        }
        printf("\n");
    }
}

void solicitar_movimiento(tPartida p)
{
    int x;
    int y;
    int jugada_realizada;
    int turno= p->turno_de;

        if (turno==PART_JUGADOR_1)
        {
            printf("\n\n\n Turno de: %s",p->nombre_jugador_1);
        }
        else
        {
            printf("\n\n\n Turno de: %s",p->nombre_jugador_2);
        }

    printf("\nIndique su jugada en fila: ");
    scanf("%d",&x);
    printf("Indique su jugada en columna: ");
    scanf("%d",&y);

    jugada_realizada = nuevo_movimiento(p,x,y);

    while (jugada_realizada==PART_MOVIMIENTO_ERROR)
    {
        printf("\n Indique un valor de fila valido: ");
        scanf("%d",&x);
        printf("Indique un valor de columna valido: ");
        scanf("%d",&y);
        jugada_realizada=nuevo_movimiento(p,x,y);
    }
}

int resultado_partida(tPartida p,int jugador)
{
    int retornar=0;
    int no_encontre_resultado=1;

    if (no_encontre_resultado==1)
    {

        if (p->tablero->grilla[0][0]!= PART_SIN_MOVIMIENTO)
        {

            if (((p->tablero->grilla[0][0] == jugador) && (p->tablero->grilla[0][1] == jugador) &&(p->tablero->grilla[0][2]==jugador)) ||
                ((p->tablero->grilla[0][0] == jugador) && (p->tablero->grilla[1][0] == jugador) &&(p->tablero->grilla[2][0]==jugador)) ||
                ((p->tablero->grilla[0][0] == jugador) && (p->tablero->grilla[1][1] == jugador) &&(p->tablero->grilla[2][2]==jugador)))
            {

                if( p->tablero->grilla[0][0] == jugador)
                {
                    retornar=1;
                    no_encontre_resultado=0;
                }
            }

        }
    }

    if (no_encontre_resultado==1)
    {

        if (p->tablero->grilla[1][1]!= PART_SIN_MOVIMIENTO)
        {

            if (((p->tablero->grilla[1][0] == jugador) && (p->tablero->grilla[1][1] == jugador) &&(p->tablero->grilla[1][2]==jugador)) ||
                ((p->tablero->grilla[0][1] == jugador) && (p->tablero->grilla[1][1] == jugador) &&(p->tablero->grilla[2][1]==jugador)) ||
                ((p->tablero->grilla[2][0] == jugador) && (p->tablero->grilla[1][1] == jugador) &&(p->tablero->grilla[0][2]==jugador)))
            {

                if (p->tablero->grilla[1][1] == jugador)
                {
                    retornar=1;
                    no_encontre_resultado=0;
                }
            }
        }
    }

    if (no_encontre_resultado==1)
    {

        if (p->tablero->grilla[2][2]!= PART_SIN_MOVIMIENTO)
        {

            if (((p->tablero->grilla[2][0] == jugador) && (p->tablero->grilla[2][1] == jugador) &&(p->tablero->grilla[2][2]==jugador)) ||
                ((p->tablero->grilla[0][2] == jugador) && (p->tablero->grilla[1][2] == jugador) &&(p->tablero->grilla[2][2]==jugador)))
            {
                if( p->tablero->grilla[2][2] == jugador)
                {
                    retornar=1;
                    no_encontre_resultado=0;
                }
            }
        }
    }
    return retornar;

}

int juego_modo_UvsU(tPartida p)
{
    int control_partida=PART_EN_JUEGO;
    int i=1;
    printf("\n Tablero: \n");
    imprimir_tablero(p);
    printf("\n\n Para jugar debe indicar su movimiento en terminos de fila y columna. En ese orden ");

    while (control_partida== PART_EN_JUEGO && i < 10 )
    {
        if ((p)->turno_de == PART_JUGADOR_1)
        {
            solicitar_movimiento(p);

            imprimir_tablero(p);

            int i= resultado_partida(p,p->turno_de);

            if (i==1)
            {
                control_partida= PART_GANA_JUGADOR_1;
                printf("\n\nGANO EL JUGADOR: %s\n\n",p->nombre_jugador_1);
            }
            (p)->turno_de = PART_JUGADOR_2;

        }
        else
        {
               // (p)->turno_de == PART_JUGADOR_2
                solicitar_movimiento(p);
                imprimir_tablero(p);
                int i= resultado_partida(p,p->turno_de);

                if (i==1)
                {
                    control_partida= PART_GANA_JUGADOR_2;
                    printf("\n\nGANO EL JUGADOR: %s\n\n",p->nombre_jugador_2);
                }
                (p)->turno_de = PART_JUGADOR_1;
        }
        i++;
    }//fin while

    if (i==10)
    {
        (p)->estado=PART_EMPATE;
        printf("\n\nFUE EMPATE!\n\n");
    }

    return 0;
}

int juego_modo_JyAgente(tPartida p)
{
    int x;
    int y;
    int jugada_realizada;
    printf("\n Tablero: \n");
    imprimir_tablero(p);
    printf("\n\n Para jugar debe indicar su movimiento en terminos de fila y columna. En ese orden \n");

    tBusquedaAdversaria b;

    while (p->estado == PART_EN_JUEGO)
    {
        if (p->turno_de ==PART_JUGADOR_1)
        {   printf("\ Jugador 1 es: %d",p->turno_de);
            solicitar_movimiento(p);
            //imprimir_tablero(p);
                 int i= resultado_partida(p,p->turno_de);

            if (i==1)
            {
                p->estado = PART_GANA_JUGADOR_1;
                printf("\n\nGANO EL JUGADOR: %s\n\n",p->nombre_jugador_1);
            }
            p->turno_de=PART_JUGADOR_2;
        }
        else //Jugador 2 AGENTE IA
        {   crear_busqueda_adversaria(&b, p);
            printf("\n ES EL TURNO DE: %d\n",p->turno_de);

            //printf("\n antes de proximo mov");
            proximo_movimiento(b,&x,&y);
           //printf("\nluego de proximo mov");
            printf("valor x: %d",x+1);
            printf("valor y : %d\n\n",y+1);
            nuevo_movimiento(p,x+1,y+1);

            imprimir_tablero(p);
            int i= resultado_partida(p,p->turno_de);

                if (i==1)
                {
                    p->estado= PART_GANA_JUGADOR_2;
                    printf("\n\nGANO EL JUGADOR: %s\n\n",p->nombre_jugador_2);
                }
            p->turno_de=PART_JUGADOR_1;
        }
    }
}

int main()
{

    int modo_juego;
    int opcion_juego;
    int comienza;
    tPartida p;

    int continuar_juego = 1;

    int estado_juego;

    char Jugador_1[30];
    char Jugador_2[30];

    printf("\n TA-TE-TI \n");
    printf("------------------------\n");

    while (continuar_juego)
    {
        modo_juego = seleccionar_modo_de_juego();

        indicar_nombres(Jugador_1,Jugador_2,modo_juego);

        printf("------------------------\n");

        comienza = seleccionar_quien_comienza(&opcion_juego, Jugador_1,Jugador_2);
        switch (modo_juego)
        {
            case 1 :
                modo_juego= PART_MODO_USUARIO_VS_USUARIO;
                nueva_partida(&p,modo_juego,comienza,Jugador_1,Jugador_2);
                estado_juego= juego_modo_UvsU(p);
                finalizar_partida(&p);
                break;
            case 2:
                nueva_partida(&p,modo_juego,comienza,Jugador_1,Jugador_2);
                modo_juego=PART_MODO_USUARIO_VS_AGENTE_IA;
                estado_juego= juego_modo_JyAgente(p);
                finalizar_partida(&p);
                break;
        }

        continuar_juego = seguir_jugando();
    }

    printf("Gracias por jugar!\n\n");
    return 0;
}

static int seleccionar_modo_de_juego()
{
    int ret_modo_juego = 0;
    printf("Opciones de partida: \n");
    printf("1 - Usuario vs Usuario: \n");
    printf("2 - Usuario vs Agente IA \n\n");
    printf("Su opcion es: ");
    scanf("%d", &ret_modo_juego);

    return ret_modo_juego;
}

static void indicar_nombres( char* jugador_1, char* jugador_2 , int modo_juego)
{
    switch (modo_juego)
    {
        case 1:
            printf("Indice nombre del Jugador 1: ");
            scanf("%s", jugador_1);
            printf("Indice nombre del Jugador 2: ");
            scanf("%s", jugador_2);
            break;
        case 2:
            printf("Indice nombre del Jugador : ");
            scanf("%s", jugador_1);
            strcpy(jugador_2,"Agente IA");
            break;
    }
}

static int seleccionar_quien_comienza(int * opcion, char * jugador_1 , char* jugador_2)
{
    int ret_comeinza = 0;

    printf("\n Indice quien comenzara la partida: \n");
    printf("1 - %s\n",jugador_1);
    printf("2 - %s\n",jugador_2);
    printf("3 - Modo Aleatorio\n");
    printf("Su opcion es: ");
    scanf("%d", opcion);

    switch (*opcion)
    {
        case 1:
            ret_comeinza = PART_JUGADOR_1;
            break;
        case 2:
            ret_comeinza = PART_JUGADOR_2;
            break;
        case 3:
            ret_comeinza = PART_JUGADOR_RANDOM;
            break;
    }

    return ret_comeinza;
}

static int seguir_jugando()
{
    int continuar_juego = 0;
    printf("Desea seguir jugando?\n");
    printf("1 - Si \n");
    printf("0 - No \n\n");
    printf("Su opcion es: ");
    scanf("%d", &continuar_juego);
    printf("\n");

    return continuar_juego;
}
#endif // MAIN_PRINCIPAL
