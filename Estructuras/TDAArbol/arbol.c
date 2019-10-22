#include "arbol.h"
#include <stdlib.h>

void (*fEliminarElementoNodo)(tElemento); // declaracion de un puntero arbol funcion.
void eliminarNodo(tElemento n);
void fEliminarListaNodos(tElemento e){}
tNodo crear_Nodo(tNodo padre, tElemento e);
tPosicion buscar_posicion_nodo(tNodo nodo);

void crear_arbol(tArbol * arbol)
{
    (*arbol) = (tArbol) malloc(sizeof(struct arbol));
    if (*arbol == NULL)
        exit(ARB_ERROR_MEMORIA);
    (*arbol)->raiz = NULL;
}

void crear_raiz(tArbol arbol, tElemento e)
{

    if (arbol->raiz != NULL)                            //Chequear excepcion
        exit(ARB_OPERACION_INVALIDA);

    arbol->raiz = crear_Nodo(NULL,e);                   //Crear nodo

}

tNodo a_insertar(tArbol arbol, tNodo nodo_padre, tNodo nodo_hermano, tElemento e)
{
    tNodo nodo_nuevo;
    tLista hijos_padre = nodo_padre->hijos;
    if (nodo_hermano != NULL)
    {
        if (nodo_hermano->padre != nodo_padre)
            exit(ARB_POSICION_INVALIDA);

        nodo_nuevo = crear_Nodo(nodo_padre,e);
        tPosicion posicion_hermano = buscar_posicion_nodo(nodo_hermano);
        l_insertar(hijos_padre,posicion_hermano,nodo_nuevo);
    }
    else
    {
        nodo_nuevo = crear_Nodo(nodo_padre,e);
        l_insertar(hijos_padre,l_fin(hijos_padre),nodo_nuevo);
    }

    return nodo_nuevo;
}

void a_eliminar(tArbol arbol, tNodo nodo, void (*fEliminar)(tElemento))
{
    int cant_hijos = l_longitud(nodo->hijos);

    if (nodo == arbol->raiz)
    {
        if (cant_hijos > 1)                 //Chequear excepcion
        {
            exit(ARB_OPERACION_INVALIDA);
        }
        if (cant_hijos == 1)
        {
            tNodo nueva_raiz = (tNodo) l_recuperar(nodo->hijos,l_primera(nodo->hijos));
            nueva_raiz->padre = NULL;
            arbol->raiz = nueva_raiz;
        }
    }
    else
    {
        tLista hermanos = nodo->padre->hijos;
        tPosicion pos_nodo_a_eliminar = buscar_posicion_nodo(nodo);
        tPosicion cursor = l_primera(nodo->hijos);
        tPosicion fin = l_fin(nodo->hijos);
        while (cursor != fin)
        {
            tNodo nodo_hijo = l_recuperar(nodo->hijos,cursor);
            nodo_hijo->padre = nodo->padre;
            l_insertar(hermanos,pos_nodo_a_eliminar, nodo_hijo);
            pos_nodo_a_eliminar = l_siguiente(hermanos,pos_nodo_a_eliminar);
            cursor = l_siguiente(nodo->hijos,cursor);
        }
        l_eliminar(hermanos,pos_nodo_a_eliminar,&fEliminarListaNodos);
    }

    l_destruir(&nodo->hijos,&fEliminarListaNodos);
    fEliminar(nodo->elemento);
    nodo->elemento = NULL;
    nodo->padre = NULL;
    free(nodo);

    nodo = NULL;

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
void a_destruir(tArbol * arbol, void (*fEliminar)(tElemento)){
    tNodo nodo_aux= (*arbol)->raiz;
    // Caso base: Solo raiz.

    fEliminarElementoNodo = fEliminar;
    l_destruir(&nodo_aux->hijos,&eliminarNodo); //elimino los hijos
    fEliminar(nodo_aux->elemento);
    free(nodo_aux);
    (*arbol)->raiz=NULL;
    free(*arbol);
    arbol=NULL;
}


/**
 Inicializa un nuevo �rbol en *SA.
 El nuevo �rbol en *SA se compone de los nodos del sub�rbol de A arbol partir de N.
 El subarbol de A arbol partir de N debe ser eliminado de A.
**/
void a_sub_arbol(tArbol arbol, tNodo nodo, tArbol * sa){

    (*sa) = (tArbol) malloc(sizeof(struct arbol));
    if (*sa == NULL)
        exit(ARB_ERROR_MEMORIA);

    tLista hermanos = nodo->padre->hijos;
    tPosicion posicion_nodo_subraiz = buscar_posicion_nodo(nodo);

    (*sa)->raiz = nodo;
    nodo->padre = NULL;
    l_eliminar(hermanos,posicion_nodo_subraiz,&fEliminarListaNodos);

}

void eliminarNodo(tElemento n){

    tNodo  nodo= (tNodo) n;

    l_destruir(&nodo->hijos, &eliminarNodo); //& porque le paso un puntero, NO una lista_hijos.
    fEliminarElementoNodo(nodo->elemento);
    nodo->padre= NULL;
    free(nodo);
}

tNodo crear_Nodo(tNodo padre, tElemento e)
{
    tNodo nodo_nuevo = (tNodo) malloc(sizeof(struct nodo));                 //Nodo arbol crear
    if (nodo_nuevo == NULL)
        exit(ARB_ERROR_MEMORIA);

    nodo_nuevo->elemento    = e;                                            //Setear elemento
    nodo_nuevo->padre       = padre;                                        //Setear padre
    crear_lista(&(nodo_nuevo->hijos));                                      //Inicializar lista_hijos de hijos

    return nodo_nuevo;
}

tPosicion buscar_posicion_nodo(tNodo nodo)
{
    tLista lista_hijos = nodo->padre->hijos;
    tPosicion posicion_a_retornar = l_primera(lista_hijos);
    tPosicion pos_fin = l_fin(lista_hijos);
    int encontre = 0;

    while ((!encontre) && (posicion_a_retornar != pos_fin))
    {
        if ((tNodo)l_recuperar(lista_hijos,posicion_a_retornar) == nodo)
        {
            encontre = 1;
        }
        else
        {
            posicion_a_retornar = l_siguiente(lista_hijos,posicion_a_retornar);
        }
    }
    return posicion_a_retornar;
}
