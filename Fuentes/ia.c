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
int max(int valor1,int valor2){

int ret = valor1;
    if(valor1<=valor2)
        ret= valor2;
return ret;
}

int min(int valor1,int valor2){

    int ret = valor2;
        if(valor1<=valor2)
            ret= valor1;

    return ret;
}

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
        tNodo nodo_de_lista= l_recuperar(lista_hijos,pos_hijo);
        estado_de_nodo_hijo=(tEstado) a_recuperar(arbol_b,nodo_de_lista);
        utilidad_de_nodo= estado_de_nodo_hijo->utilidad;
        if (utilidad_de_nodo==utilidad_padre)
        {
            corte=1;
        }
        else
        {
            pos_hijo=l_siguiente(lista_hijos,pos_hijo);
            cursor++;
        }

    }
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

    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
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
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){
    ///Guardo en una variable auxiliar el elemento del nodo encontrado en el arbol y el nodo pasados por paramentro.
    ///Ejecuto la funcion minimax pasando por parametro el elemento del nodo anteriormente guardado,el entero que identifica al jugador y dos variables que identifican el valor de utilidad.
   ///Declaracion de variables.
    tEstado estado=n->elemento;
    tLista sucesores;
    tPosicion posActualSucesores;
    tPosicion finSucesores;
    tEstado sucesorAct;
    int encontro = 0;

    ///Si es un estado final devuelve la utilidad.
    estado->utilidad=valor_utilidad(estado,jugador_max);
    if(estado->utilidad==IA_NO_TERMINO){
        ///Si esJugadorMax !=0 significa que es un estado max.
        if(es_max){
            ///Inicializo las variables.
            sucesores = estados_sucesores(estado,jugador_max);
            posActualSucesores = l_primera(sucesores);
            finSucesores = l_fin(sucesores);
            ///Exploro la lista de estados hijos del estado actual.
            while(posActualSucesores!=finSucesores&&!encontro){
                    ///Recupero el estado de la posicion de la lista de hijos.
                    sucesorAct = (tEstado) l_recuperar(sucesores,posActualSucesores);
                    ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado min.
                    sucesorAct->utilidad=valor_utilidad(sucesorAct,jugador_max);
                    tNodo hijoActual = a_insertar(a,n,NULL,sucesorAct);
                    crear_sucesores_min_max(a,hijoActual,0,alpha,beta,jugador_max,jugador_min);//Este esta bien.Creo, le paso 0 para que vaya al else.
                    ///Si la utilidad del hijo es mayor a la anteriormente calculada la reemplazo por el nuevo valor.
                    tEstado estadoSucesor = hijoActual->elemento;
                    //if(estadoSucesor->utilidad<mejorValorSucesores)
                    //    mejorValorSucesores= caca->utilidad;
                    ///Si alpha es menor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                    if(alpha<estadoSucesor->utilidad)
                        alpha = estadoSucesor->utilidad;
                    ///Si beta es menor  o igual a alpha, podo.
                    if(beta<=alpha){
                        encontro = 1;
                    }
                    ///Actualizo la posicion en la lista de hijos.
                    posActualSucesores = l_siguiente(sucesores,posActualSucesores);
            }
            estado->utilidad = alpha;
        }
        ///Si esJugadorMax =0 significa que es un estado min.
        else{
            ///Inicializo las variables.
            sucesores = estados_sucesores(estado,jugador_min);
            posActualSucesores = l_primera(sucesores);
            finSucesores = l_fin(sucesores);
            ///Exploro la lista de estados hijos del estado actual.
            while(posActualSucesores!=finSucesores&&!encontro){
                    ///Recupero el estado de la posicion de la lista de hijos.
                    sucesorAct = (tEstado) l_recuperar(sucesores,posActualSucesores);
                    ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado max.
                    tNodo hijoActual =a_insertar(a,n,NULL,sucesorAct);
                    sucesorAct->utilidad=valor_utilidad(sucesorAct,jugador_max);
                    crear_sucesores_min_max(a,hijoActual,1,alpha,beta,jugador_max,jugador_min);//Este le paso para que en el sig vaya al if y no al else
                    ///Si la utilidad del hijo es menor a la anteriormente calculada la reemplazo por el nuevo valor.
                    tEstado estadoSucesor=hijoActual->elemento;
                    ///Si beta es mayor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                    if(estadoSucesor->utilidad<beta)
                        beta = estadoSucesor->utilidad;
                    ///Si beta es menor  o igual a alpha, podo.
                    if(beta<=alpha){
                        encontro = 1;
                    }
                    ///Actualizo la posicion en la lista de hijos.
                    posActualSucesores = l_siguiente(sucesores,posActualSucesores);
            }
            estado->utilidad = beta;
        }
    l_destruir(&sucesores,&fNoEliminar);
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
static int valor_utilidad(tEstado e, int jugador_max){
    ///Retorno el entero conseguido al ejecutar la funcion gano con el estado pasado por parametro
    ///y la variable que representa al jugador tambien pasada por parametro.
    int gano1=0;
    int gano2=0;

    int ficha1=jugador_max;
    int ficha2=0;

    int espaciosVacios=0;
    int i=0;

    if(jugador_max==PART_JUGADOR_1)
        ficha2=PART_JUGADOR_2;
    else{
        ficha2=PART_JUGADOR_1;
    }
        ///Chequeo las filas.
        while(gano1!=3 && gano2!=3 && i<3){
            for(int j=0; j<3; j++){
                ///si esta la ficha, aumento su variable gano
                if(e->grilla[i][j]==ficha1){
                    gano1++;
                }
                if(e->grilla[i][j]==ficha2){
                    gano2++;
                }
                if(e->grilla[i][j]==PART_SIN_MOVIMIENTO){
                    espaciosVacios++;
                }
            }
            if(gano1>=3)
                return IA_GANA_MAX;
            if(gano2>=3)
                return IA_PIERDE_MAX;
            gano2=0;
            gano1=0;
            i++;
        }

        int j=0;
        ///Chequeo las columnas.
        while(gano1!=3 && gano2!=3 && j<3){
            for(i=0; i<3; i++){
                ///si esta la ficha, aumento su variable gano
                if(e->grilla[i][j]==ficha1)
                    gano1++;
                if(e->grilla[i][j]==ficha2)
                    gano2++;
                if(e->grilla[i][j]==PART_SIN_MOVIMIENTO)
                    espaciosVacios++;
                }
            if(gano1>=3)
                return IA_GANA_MAX;
            if(gano2>=3)
                return IA_PIERDE_MAX;
            gano1=0;
            gano2=0;
            j++;
        }
        //diagonal hardcodeada x2
        i=0; j=0;
        while(j<3 && i<3){
             ///si esta la ficha, aumento su variable gano
            if(e->grilla[i][j]==ficha1)
                gano1++;
            if(e->grilla[i][j]==ficha2)
                gano2++;
            if(e->grilla[i][j]==PART_SIN_MOVIMIENTO)
                espaciosVacios++;
            i++;
            j++;
        }
        if(gano1>=3)
            return IA_GANA_MAX; //gano1
        if(gano2>=3)
            return IA_PIERDE_MAX;

        gano1=0;
        gano2=0;
        i=-1;
        j=3;
        while(j>0 && i<3){
            j--;
            i++;
            ///si esta la ficha, aumento su variable gano
            if(e->grilla[i][j]==ficha1)
                gano1++;
            if(e->grilla[i][j]==ficha2)
                gano2++;
            if(e->grilla[i][j]==PART_SIN_MOVIMIENTO)
                espaciosVacios++;
        }
        if(gano1>=3)
            return IA_GANA_MAX; //gano1
        if(gano2>=3)
            return IA_PIERDE_MAX;
        if(espaciosVacios==0)
            return IA_EMPATA_MAX;
    return IA_NO_TERMINO;
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

    for ( fila ; fila < 3 ; fila++ )
    {
        for ( columna ; columna < 3 ; columna++ )
        {
            valor_grilla=e->grilla[fila][columna];

            if (valor_grilla==PART_SIN_MOVIMIENTO)   // Es una casilla libre
            {
                estado_clon= clonar_estado(e); //clono el estado original


                estado_clon->grilla[fila][columna]=ficha_jugador; // agrego la ficha del jugador al lugar correspondiente.
                //numero random
                int numero_random= rand()%2;
                if (numero_random)  //1
                {
                    l_insertar(lista_con_sucesores,l_fin(lista_con_sucesores),estado_clon);
                }
                else                //0
                {
                    l_insertar(lista_con_sucesores,l_primera(lista_con_sucesores),estado_clon);
                }
                tEstado pos=l_recuperar(lista_con_sucesores,l_primera(lista_con_sucesores));
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



