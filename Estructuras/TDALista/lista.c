#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

void fEliminar(tElemento e);

void crear_lista(tLista* l)
{
    (*l) = (tLista) malloc(sizeof(struct celda));

    if (*l == NULL)
        exit(LST_ERROR_MEMORIA);

    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

void l_insertar(tLista l, tPosicion p, tElemento e)
{
    tPosicion nodo_nuevo = (tPosicion) malloc(sizeof(struct celda));
    if (nodo_nuevo == NULL)
        exit(LST_ERROR_MEMORIA);

    nodo_nuevo->elemento = e;
    nodo_nuevo->siguiente = p->siguiente;
    p->siguiente = nodo_nuevo;
}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento))
{
    if (p == l_fin(l))
        exit(LST_POSICION_INVALIDA);

    fEliminar((p->siguiente)->elemento);
    (p->siguiente)->elemento = NULL;
    p->siguiente = (p->siguiente)->siguiente;
    tPosicion pos_NULL = p->siguiente;
    free(pos_NULL);
    pos_NULL = NULL;
}

void l_destruir(tLista * l, void (*fEliminar)(tElemento))
{
    while ((*l)->siguiente != NULL)
        l_destruir((*l)->siguiente, *fEliminar);

    fEliminar((*l)->elemento);
    (*l)->elemento  = NULL;
    (*l)->siguiente = NULL;
    free(*l);
    *l = NULL;
}

tElemento l_recuperar(tLista l, tPosicion p)
{
    if (p == l_fin(l))
        exit(LST_POSICION_INVALIDA);
    return (p->siguiente)->elemento;

}

tPosicion l_primera(tLista l)
{
    return l;
}

tPosicion l_siguiente(tLista l, tPosicion p)
{
    if (p == l_fin(l))
        exit(LST_NO_EXISTE_SIGUIENTE);

    return p->siguiente;
}

tPosicion l_anterior(tLista l, tPosicion p)
{
    if(p == l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);

    tPosicion nodo_actual = l;
    while(nodo_actual->siguiente != p && nodo_actual->siguiente != NULL)
        nodo_actual = nodo_actual->siguiente;

    return nodo_actual;
}

tPosicion l_ultima(tLista l)
{
    tPosicion nodo_actual = l;

    while (nodo_actual->siguiente != NULL && (nodo_actual->siguiente)->siguiente != NULL)
            nodo_actual = nodo_actual->siguiente;

    return nodo_actual;
}

tPosicion l_fin(tLista l)
{
    tPosicion toRet = l;

    while (toRet->siguiente != NULL)
        toRet = toRet->siguiente;

    return toRet;
}

int l_longitud(tLista l)
{
    int contador = 0;
    tPosicion nodo = l;
    while (nodo->siguiente != NULL)
    {
        nodo = nodo->siguiente;
        contador++;
    }
    return contador;
}
