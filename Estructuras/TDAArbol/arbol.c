#include "arbol.h"
#include <stdlib.h>

void (*fEliminarElementoNodo)(tElemento); // declaracion de un puntero arbol funcion.
void eliminarNodo(tElemento n);
void fEliminarListaNodos(tElemento e){}
tNodo crear_Nodo(tNodo padre, tElemento e);

tPosicion buscar_posicion_nodo(tLista lista, tNodo nodo)
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
    tNodo nodo_nuevo;
    tLista hijos_padre = nodo_padre->hijos;
    if (nodo_hermano != NULL)
    {
        if (nodo_hermano->padre != nodo_padre)
            exit(ARB_POSICION_INVALIDA);

        nodo_nuevo = crear_Nodo(nodo_padre,e);
        tPosicion posicion_hermano = buscar_posicion_nodo(hijos_padre,nodo_hermano);
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
            arbol->raiz = nueva_raiz;
        }
    }
    else
    {
        tNodo padre = nodo->padre;
        tLista hijos = padre->hijos;
        tPosicion pos_nodo_a_eliminar = buscar_posicion_nodo(hijos,nodo);

        tPosicion cursor = l_primera(nodo->hijos);
        tPosicion fin = l_fin(nodo->hijos);
        while (cursor != fin)
        {
            l_insertar(hijos,pos_nodo_a_eliminar,l_recuperar(nodo->hijos,cursor));
        }
    }
        l_destruir(&nodo->hijos,&fEliminarListaNodos);
        fEliminar(nodo->elemento);
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
    free(arbol);
    arbol=NULL;
}


/**
 Inicializa un nuevo �rbol en *SA.
 El nuevo �rbol en *SA se compone de los nodos del sub�rbol de A arbol partir de N.
 El subarbol de A arbol partir de N debe ser eliminado de A.
**/
void a_sub_arbol(tArbol arbol, tNodo n, tArbol * sa){

    (*sa) = (tArbol) malloc(sizeof(struct arbol));
    if (*sa == NULL)
        exit(ARB_ERROR_MEMORIA);

    tNodo padre = n->padre;
    tLista hijos = padre->hijos;
    tPosicion posicion_nodo_subraiz = buscar_posicion_nodo(hijos,n);

    (*sa)->raiz = n;
    n->padre = NULL;
    l_eliminar(hijos,posicion_nodo_subraiz,&fEliminarListaNodos);

}
/*
void subArbol_rec(tArbol arbol,tNodo nodoA, tArbol *sa, tNodo nodoSA ){

    for(tPosicion * posA = nodoA->hijos; posA!= NULL; posA= l_siguiente(nodoA->hijos,posA)){ //recorro la lista de hijos del nodo de A
    l_insertar(nodoSA->hijos,l_fin(nodoSA->hijos) , posA->elemento);

    tElemento ultimo= l_ultima(nodoSA->hijos)->elemento;
    tNodo ul= (tNodo) ultimo;

    subArbol_rec(arbol,posA, sa,posA->elemento);
    }

}*/

void eliminarNodo(tElemento n){

    tNodo  nodo= (tNodo) n;

    l_destruir(&nodo->hijos, &eliminarNodo); //& porque le paso un puntero, NO una lista.
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
    tLista lista_hijos_nn;
    crear_lista(&lista_hijos_nn);                                           //Inicializar lista de hijos
    nodo_nuevo->hijos = lista_hijos_nn;                                     //Setear lista de hijos

    return nodo_nuevo;
}
