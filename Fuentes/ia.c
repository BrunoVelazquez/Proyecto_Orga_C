#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "lista.h"
#include "arbol.h"
#include "ia.h"

// Prototipos de funciones auxiliares.
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);

void fNoEliminar(tElemento e){};
void fEliminar(tElemento e){
    free(e);
    e = NULL;
}
/**
 Inicializa la estructura correspondiente a una b�squeda adversaria, a partir del estado actual de la partida parametrizada.
 Se asume la partida parametrizada con estado PART_EN_JUEGO.
 Los datos del tablero de la partida parametrizada son clonados, por lo que P no se ve modificada.
 Una vez esto, se genera el �rbol de b�squeda adversaria siguiendo el algoritmo Min-Max con podas Alpha-Beta.
**/
void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p)
{
    int i, j;
    tEstado estado;

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));

    if ((*b) == NULL)
        exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));

    if (estado == NULL)
        exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la b�squeda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representar�n a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un �rbol para la b�squeda adversaria inicialmente vac�o.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la ra�z del �rbol de b�squeda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

/**
>>>>>  A IMPLEMENTAR   <<<<<   PREGUNTAR PORQUE ESTA PARCIALMENTE IMPLEMENTADO
*/
/**
 Computa y retorna el pr�ximo movimiento a realizar por el jugador MAX.
 Para esto, se tiene en cuenta el �rbol creado por el algoritmo de b�squeda adversaria Min-max con podas Alpha-Beta.
 Siempre que sea posible, se indicar� un movimiento que permita que MAX gane la partida.
 Si no existe un movimiento ganador para MAX, se indicar� un movimiento que permita que MAX empate la partida.
 En caso contrario, se indicar� un movimiento que lleva a MAX a perder la partida.
**/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y)
{
    tArbol arbol_b= b->arbol_busqueda;

    tNodo nodo_raiz= a_raiz(arbol_b);
    tEstado estado_de_nodo_padre=(tEstado) a_recuperar(arbol_b,nodo_raiz);
    int utilidad_padre=estado_de_nodo_padre->utilidad;
   // printf("Utilidad del nodo padre: %d",utilidad_padre);

    tLista lista_hijos =a_hijos(arbol_b,nodo_raiz);

    int longitud_lista=l_longitud(lista_hijos);
    tPosicion pos_hijo=l_primera(lista_hijos);

    tEstado estado_de_nodo_hijo;
    int utilidad_de_nodo;
    int cursor=0;
    int corte=0;

    while (cursor<longitud_lista && corte==0)
    {
       // printf("\n cursor: %d",cursor);
        tNodo nodo_de_lista= l_recuperar(lista_hijos,pos_hijo);
        estado_de_nodo_hijo=(tEstado) a_recuperar(arbol_b,nodo_de_lista);
        //printf("\n");
        //imprimirr(estado_de_nodo_hijo);
        utilidad_de_nodo= estado_de_nodo_hijo->utilidad;
       // printf("\n Utilidad del padre: %d",utilidad_padre);
       //) printf("\n utilidad nodo hijo: %d",utilidad_de_nodo);
       // printf("\n ");
        if (utilidad_de_nodo==utilidad_padre){
            corte=1;}
        else

        {pos_hijo=l_siguiente(lista_hijos,pos_hijo);
        cursor++;
        }

    }
    //printf("fin while");
    diferencia_estados(estado_de_nodo_padre, estado_de_nodo_hijo,x,y);

}

/**
>>>>>  A IMPLEMENTAR   <<<<< LISTOOOOOO
 Libera el espacio asociado a la estructura correspondiente para la b�squeda adversaria.
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b)
{
    (*b)->jugador_max= -1;
    (*b)->jugador_min= -1;
    a_destruir(&((*b)->arbol_busqueda), &fEliminar);
    free(*b);
    *b = NULL;
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecuci�n del algoritmo Min-Max para la generaci�n del �rbol de b�squeda adversaria, considerando como
estado inicial el estado de la partida almacenado en el �rbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    tArbol a = b->arbol_busqueda;
    tNodo r = a_raiz(a);
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;

   // printf("\n EN EJECUTAR MIN MAX, JUGADOR MAX ES: %d",jugador_max);
    // printf("\n EN EJECUTAR MIN MAX, JUGADOR MIN ES: %d",jugador_min);
    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

int max(int valor1,int valor2){

int ret;
    if(valor1<=valor2) ret= valor2;
    else ret=valor1;
return ret;
}

int min(int valor1,int valor2){

int ret;
    if(valor1<=valor2) ret= valor1;
    else ret=valor2;
return ret;
}

/**
>>>>>  A IMPLEMENTAR   <<<<< LISTOOOOO
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al �rbol de b�squeda adversaria.
- N referencia al nodo a partir del cual se construye el sub�rbol de b�squeda adversaria.
- ES_MAX indica si N representa un nodo MAX en el �rbol de b�squeda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el �rbol de b�squeda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min)
{
    int mejor_valor_sucesores;
    int corte;
    tLista lista_sucesores;
    int longitud;
    int cursor;
    int utilidad_del_estado;
    tEstado estadoN= (tEstado) a_recuperar(a,n);

    if( valor_utilidad(estadoN, jugador_max)!= (IA_NO_TERMINO)){ // Esta bien
         estadoN->utilidad= valor_utilidad(estadoN,jugador_max);
            //printf("ES UN ESTADO TERMINAL. Valor de utilidad: %d\n",estadoN->utilidad);}
}
    if(es_max){
                mejor_valor_sucesores= IA_INFINITO_NEG;

                corte=0;
                lista_sucesores = estados_sucesores(estadoN,jugador_max);
                longitud= l_longitud(lista_sucesores);
                cursor=0;

                while(cursor<longitud && corte==0){

                    tEstado estado_de_l= l_recuperar(lista_sucesores, l_primera(lista_sucesores));
                    l_eliminar(lista_sucesores,l_primera(lista_sucesores),&fNoEliminar);
                    tNodo nodo_nuevo= a_insertar(a, n, NULL, estado_de_l);

                    crear_sucesores_min_max(a,nodo_nuevo,0,alpha,beta,jugador_max,jugador_min);

                    tEstado estado_nuevo_nodo= (tEstado) a_recuperar(a,nodo_nuevo);
                   // printf("\n luego de crear suc en max\n ");
                    // imprimirr(estado_nuevo_nodo);
                    // printf("\n");
                     //
                                 //printf("\n ESTADO DEL NODO RECUPERADO LUEGO DE CS en max: %d \n",estado_nuevo_nodo->utilidad);
                    utilidad_del_estado=estado_nuevo_nodo->utilidad;
                    // printf("\nutilidad del estado: %d",utilidad_del_estado);
                    mejor_valor_sucesores=max(mejor_valor_sucesores,utilidad_del_estado);

                    alpha=max(alpha,mejor_valor_sucesores);

                    if(beta<=alpha){ corte=1;} // dejo de explorar la lista de sucesores. Podo.
                      estadoN->utilidad= mejor_valor_sucesores;
                    cursor=cursor+1;
                }
            }
            else{ //es jugador min.
                    mejor_valor_sucesores= IA_INFINITO_POS;
                    corte=0;
                    lista_sucesores = estados_sucesores(estadoN,jugador_min);
                    longitud= l_longitud(lista_sucesores);
                    cursor=0;

                    while(cursor<longitud && corte==0){

                        tEstado estado_de_l= (tEstado) l_recuperar(lista_sucesores, l_primera(lista_sucesores));
                        l_eliminar(lista_sucesores,l_primera(lista_sucesores),&fNoEliminar);
                        tNodo nodo_nuevo = a_insertar(a, n, NULL, estado_de_l);

                        crear_sucesores_min_max(a,nodo_nuevo,1,alpha,beta,jugador_max,jugador_min);

                        tEstado estado_nuevo_nodo= a_recuperar(a,nodo_nuevo);
                           // printf("\n luego de crear suc en min \n");
                        // imprimirr(estado_nuevo_nodo);

                         //  printf("\n");
                        utilidad_del_estado= estado_nuevo_nodo->utilidad;
                        //printf("\n utilidad del estado: %d",utilidad_del_estado);
                        mejor_valor_sucesores=min(estado_nuevo_nodo->utilidad,mejor_valor_sucesores);

                        beta=min(beta,mejor_valor_sucesores);

                        if(beta <= alpha)
                                {corte=1;}

                        estadoN->utilidad= mejor_valor_sucesores;

                        cursor=cursor+1;
                         //estadoN->utilidad= estado_nuevo_nodo->utilidad;

                  //  printf("\n El estado del mejor valor sucesor: %d",estadoN->utilidad);

                }
            }



        l_destruir(&lista_sucesores,&fEliminar);



}


void imprimirr(tEstado e){
{
    for ( int i = 0 ; i < 3 ; i++ )
    {
        for ( int j = 0 ; j < 3; j++ )
        {
            if (e->grilla[i][j]==PART_SIN_MOVIMIENTO)
            {
                printf(" [   ] ");
            }
            else
            {
                if (e->grilla[i][j] ==PART_JUGADOR_1)
                {
                    printf(" [ X ] ");
                }
                else
                {
                    printf(" [ 0 ] ");
                }
            }
        }
        printf("\n");
    }
}
}

/**
>>>>>  A IMPLEMENTAR   <<<<< LISTOOOOOOOOOOO
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX gan� la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empat� la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdi� la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max)
{ //printf("\n JUGADOR MAX ES: %d",jugador_max);
    int ret=IA_EMPATA_MAX;
    int no_encontre_resultado=1;

    if(no_encontre_resultado==1){

     if(( e->grilla[0][0])!=PART_SIN_MOVIMIENTO){



          if (((e->grilla[0][0] == jugador_max) && (e->grilla[0][1] == jugador_max) && ( e->grilla[0][2] == jugador_max)) ||
              ((e->grilla[0][0] == jugador_max) && (e->grilla[1][0] == jugador_max) && ( e->grilla[2][0] == jugador_max)) ||
              ((e->grilla[0][0] == jugador_max) && (e->grilla[1][1] == jugador_max) && ( e->grilla[2][2] == jugador_max))){

                if(( e->grilla[0][0]) == jugador_max) {
                       // ret= IA_GANA_MAX;
                        //printf("\n entre  a este if 1");
                        no_encontre_resultado=0;
                        ret= IA_PIERDE_MAX;
                }
                  else
                      {ret= IA_GANA_MAX;
                              //  ret= IA_PIERDE_MAX;
                                printf("\n entre a IA PIERDE MAX");
                                no_encontre_resultado=0;
                }
            }
        }


     }//fin no encontre resultado.

     if(no_encontre_resultado==1){

     if((e->grilla[1][1])!=PART_SIN_MOVIMIENTO){

        if(   ((e->grilla[1][0] == jugador_max) && (e->grilla[1][1]==jugador_max) && (e->grilla[1][2] ==jugador_max)) ||
              (( e->grilla[0][1] == jugador_max) && (e->grilla[1][1]== jugador_max) && ( e->grilla[2][1]==jugador_max)) ||
              ((e->grilla[2][0] == jugador_max) && (e->grilla[1][1]==jugador_max) && ( e->grilla[0][2]== jugador_max))){
                if((e->grilla[1][1]) == jugador_max) {
                       // ret= IA_GANA_MAX;
                        // printf("\n entre  a este if 2");
                        no_encontre_resultado=0;
                         ret= IA_PIERDE_MAX;
                }

                else
                {                        ret= IA_GANA_MAX;
                 // ret= IA_PIERDE_MAX;
                  printf("\n entre a IA PIERDE MAX");
                 no_encontre_resultado=0;
                }
            }
        }


     }//fin no encontre resultado


     if(no_encontre_resultado==1){

     if((e->grilla[2][2])!=PART_SIN_MOVIMIENTO){

        if (  ((e->grilla[2][0] == jugador_max) && (e->grilla[2][1]==jugador_max) && (e->grilla[2][2] ==jugador_max)) ||
              (( e->grilla[0][2] == jugador_max) && (e->grilla[1][2]== jugador_max) && ( e->grilla[2][2]==jugador_max)) ){
                if((e->grilla[2][2])== jugador_max) {
                      //  ret= IA_GANA_MAX;
                         //printf("\n entre  a este if 3");
                        no_encontre_resultado=0;
                           ret= IA_PIERDE_MAX;
                }
                  else
                {ret= IA_GANA_MAX;
                                  printf("\n entre a IA PIERDE MAX");
                                 //   ret= IA_PIERDE_MAX;
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
                if (e->grilla[i][j]!= PART_SIN_MOVIMIENTO)
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


/**
>>>>>  A IMPLEMENTAR   <<<<<   CORREGIDO
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonaci�n del estado E, junto con la incorporaci�n de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posici�n que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocaci�n de la funci�n
estados_sucesores(estado, ficha) retornar�a dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador)
{
    tLista lista_con_sucesores;
    crear_lista(&lista_con_sucesores);
    tEstado estado_clon;

    int fila=0;
    int columna=0;
    int valor_grilla;

    srand(time(NULL));

    for ( fila ; fila < 3 ; fila++ )
    {
        for ( columna ; columna < 3 ; columna++ )
        {
            valor_grilla=e->grilla[fila][columna];
            //printf("\n Valor grilla(list estados sucesores: %d",valor_grilla);


            if (valor_grilla==PART_SIN_MOVIMIENTO)   // Es una casilla libre
            {
               // printf("\n Se inserta en fila:  %d",fila);
               // printf("      Se inserta en columna:  %d",columna);
                estado_clon= clonar_estado(e); //clono el estado original


                estado_clon->grilla[fila][columna]=ficha_jugador; // agrego la ficha del jugador al lugar correspondiente.
                //printf("\n Estado sucesore con LA FICHA %d",estado_clon->grilla[fila][columna]);

                   //numero random
                int numero_random= rand()%2;

                if (numero_random==1)
                {
                     l_insertar(lista_con_sucesores,l_fin(lista_con_sucesores),estado_clon);
                }
                else
                {
                    l_insertar(lista_con_sucesores,l_primera(lista_con_sucesores),estado_clon);
                }

                tEstado pos=l_recuperar(lista_con_sucesores,l_primera(lista_con_sucesores));
                int es= pos->utilidad;
                //printf("\n utilidad del estado que agregue a la lista: %d",es);
            }
        }
        columna=0;
    }
    return lista_con_sucesores;
}

/**
>>>>>  A IMPLEMENTAR   <<<<< LISTOOOOOOO
Inicializa y retorna un nuevo estado que resulta de la clonaci�n del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e)
{
    int i;
    int j;
    tEstado estado_clon = (tEstado) malloc(sizeof(struct estado));
    estado_clon->utilidad = e->utilidad;

    for ( i = 0 ; i < 3 ; i++ )
    {
        for ( j = 0 ; j < 3 ; j++ )
        {
            estado_clon->grilla[i][j] = e->grilla[i][j];
        }
    }
    return estado_clon;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe s�lo una posici�n en el que la ficha del estado anterior y nuevo difiere.
La posici�n en la que los estados difiere, es retornada en los par�metros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    int i,j, hallado = 0;

    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}



