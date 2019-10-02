#include "arbol.h"
#include <stdlib.h>

//void fEliminar(tElemento e);

void (*fEliminarNodo)(tElemento) // declaracion de un puntero a funcion.
void eliminarNodos(tElemento n);

tPosicion buscar_nodo_hermano(tLista lista, tNodo nodo)
{
    tPosicion posicion_a_retornar = l_primera(lista);
    tPosicion pos_fin = l_fin(lista);

    while ((posicion_a_retornar != pos_fin) && (l_recuperar(lista,posicion_a_retornar) != nodo))
    {
        posicion_a_retornar = l_siguiente(lista,posicion_a_retornar);
    }
    return posicion_a_retornar;
}

void crear_arbol(tArbol * arbol)
{
    (*arbol) = (tArbol) malloc(sizeof(struct arbol));
    if (*arbol == NULL)
        exit(ARB_ERROR_MEMORIA);
}

void crear_raiz(tArbol arbol, tElemento e)
{
    tNodo nodo_raiz = arbol->raiz;

    if (nodo_raiz != NULL)                              //Chequear excepcion
        exit(ARB_OPERACION_INVALIDA);

    nodo_raiz = (tNodo) malloc(sizeof(struct nodo));    //Crear nodo nuevo

    if (nodo_raiz == NULL)                              //Chequear memoria
        exit(ARB_ERROR_MEMORIA);

    nodo_raiz->elemento = e;                            //Setear elemento
    nodo_raiz->padre    = NULL;                         //Setear como 'raiz'
    crear_lista(&(nodo_raiz->hijos));                   //Inicializar lista de hijos
}

tNodo a_insertar(tArbol arbol, tNodo nodo_padre, tNodo nodo_hermano, tElemento e)
{
    if (nodo_hermano->padre != nodo_padre)                  //Chequear NH tiene como padre a NP
        exit(ARB_POSICION_INVALIDA);

    tNodo nodo_nuevo = (tNodo) malloc(sizeof(struct nodo)); //Nodo a crear
    if (nodo_nuevo == NULL)
        exit(ARB_ERROR_MEMORIA);

    nodo_nuevo->elemento    = e;                            //Setear elemento
    nodo_nuevo->padre       = nodo_padre;                   //Setear padre
    tLista lista_hijos_nn;
    crear_lista(&lista_hijos_nn);                           //Inicializar lista de hijos
    nodo_nuevo->hijos = lista_hijos_nn;                     //Setear lista de hijos
    
    tLista hijos_padre = nodo_padre->hijos;
    if (nodo_hermano == NULL)
    {
        l_insertar(hijos_padre,l_fin(hijos_padre),nodo_nuevo);
    }
    else
    {
        tPosicion posicion_hermano = buscar_posicion_hermano(hijos_padre,nodo_hermano);
        l_insertar(hijos_padre,posicion_hermano,nodo_nuevo);
    }

    return nodo_nuevo;
}

void a_eliminar(tArbol arbol, tNodo nodo, void (*fEliminar)(tElemento))
{
    int cant_hijos = l_longitud(nodo->hijos);

    if ((nodo == arbol->raiz) && (cant_hijos > 1)) //Chequear excepcion
        exit(ARB_OPERACION_INVALIDA);

    if ((nodo == arbol->raiz) && (cant_hijos == 1))
    {
        tNodo nueva_raiz = l_primera(nodo->hijos);
        fEliminar(nodo->elemento);
        free(nodo);
        nodo = NULL;
        arbol->raiz = nueva_raiz;
    }

    if ((nodo != arbol->raiz) && (cant_hijos > 1))
    {
        tNodo padre = nodo->padre;

    }
}

tElemento a_recuperar(tArbol arbol, tNodo nodo)
{
    return nodo->elemento;
}

tNodo a_raiz(tArbol arbol)
{
    return arbol->raiz;
}

tLista a_hijos(tArbol arbol, tNodo nodo)
{
    return nodo->hijos;
}

/**
 Destruye el �rbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el �rbol son eliminados mediante la funci�n fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    tNodo nodo_aux= *a->raiz;
    // Caso base: Solo raiz.
    l_destruir(&nodo_aux->hijos,&eliminarNodos); //elimino los hijos
    fEliminar(nodo_aux->elemento);
    free(nodo_aux);
    *a->raiz=NULL;
    free(a);
    a=NULL;
}


/**
 Inicializa un nuevo �rbol en *SA.
 El nuevo �rbol en *SA se compone de los nodos del sub�rbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
void a_sub_arbol(tArbol a, tNodo n, tArbol * sa){

    (*sa) = (tArbol) malloc(sizeof(struct arbol));
    if (*sa == NULL)
        exit(ARB_ERROR_MEMORIA);

    sa->raiz = n->elemento;


        }
void eliminarNodos(tElemento n){

    tNodo  nodo= (tNodo) n;
    l_destruir(&nodo->hijos, &eliminarNodos); //& porque le paso un puntero, NO una lista.
    fEliminarNodo(nodo);
    nodo->padre= NULL;
    free(nodo);
}
