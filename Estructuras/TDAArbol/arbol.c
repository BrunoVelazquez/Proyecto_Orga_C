#include "arbol.h"
#include <lista.h>
#include <stdlib.h>

void crear_arbol(tArbol * arbol)
{
    (*arbol) = (tArbol) malloc(sizeof(struct arbol));
    if (arbol == NULL)
        exit(ARB_ERROR_MEMORIA);
}

void crear_raiz(tArbol arbol, tElemento e)
{
    tNodo nodo_raiz = arbol->raiz;

    if (nodo_raiz != NULL)
        exit(ARB_OPERACION_INVALIDA);

    nodo_raiz = (tNodo) malloc(sizeof(struct nodo));

    if (nodo_raiz == NULL)
        exit(ARB_ERROR_MEMORIA);

    nodo_raiz->elemento = e;
    nodo_raiz->padre    = NULL;
    crear_lista(&(nodo_raiz->hijos));
}

tNodo a_raiz(tArbol arbol)
{
    
    return arbol->raiz;
}
