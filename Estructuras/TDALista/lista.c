#include "lista.h"
#include <stdlib.h>

void destruirREC(tPosicion pos, void(*fEliminar)(tElemento));

void crear_lista(tLista* lista)
{
    (*lista) = (tLista) malloc(sizeof(struct celda));
    if (*lista == NULL)
        exit(LST_ERROR_MEMORIA);

    (*lista)->elemento = NULL;
    (*lista)->siguiente = NULL;
}

void l_insertar(tLista lista, tPosicion pos, tElemento e)
{
    tPosicion celda_nueva = (tPosicion) malloc(sizeof(struct celda));
    if (celda_nueva == NULL)
        exit(LST_ERROR_MEMORIA);

    celda_nueva->elemento = e;
    celda_nueva->siguiente = pos->siguiente;
    pos->siguiente = celda_nueva;
}

void l_eliminar(tLista lista, tPosicion pos, void (*fEliminar)(tElemento))
{
    if (pos->siguiente == NULL)
        exit(LST_POSICION_INVALIDA);
    fEliminar((pos->siguiente)->elemento);
    tPosicion pos_NULL = pos->siguiente;
    pos->siguiente = pos_NULL->siguiente;
    pos_NULL->elemento  = NULL;
    pos_NULL->siguiente = NULL;
    free(pos_NULL);
}

void l_destruir(tLista * lista, void (*fEliminar)(tElemento))
{
    tPosicion centinela = *lista;

    if (centinela->siguiente != NULL)
    {
        destruirREC(centinela->siguiente,fEliminar);
    }

    centinela->siguiente = NULL;
    free(centinela);
    *lista= NULL;
}

void destruirREC(tPosicion pos, void(*fEliminar)(tElemento))
{
    if (pos->siguiente != NULL)
    {
        destruirREC(pos->siguiente, fEliminar);
    }

    fEliminar(pos->elemento);
    pos->elemento  = NULL;
    pos->siguiente = NULL;
    free(pos);
}

tElemento l_recuperar(tLista lista, tPosicion pos)
{
    if (pos->siguiente == NULL)
        exit(LST_POSICION_INVALIDA);

    return (pos->siguiente)->elemento;
}

tPosicion l_primera(tLista lista)
{
    return lista;
}

tPosicion l_siguiente(tLista lista, tPosicion pos)
{
    if (pos->siguiente == NULL)
        exit(LST_NO_EXISTE_SIGUIENTE);

    return pos->siguiente;
}

tPosicion l_anterior(tLista lista, tPosicion pos)
{
    if(pos == lista)
        exit(LST_NO_EXISTE_ANTERIOR);

    tPosicion celda_actual = lista;
    while(celda_actual->siguiente != pos && celda_actual->siguiente != NULL)
    {
        celda_actual = celda_actual->siguiente;
    }

    return celda_actual;
}

tPosicion l_ultima(tLista lista)
{
    tPosicion celda_actual = lista;
    while (celda_actual->siguiente != NULL && (celda_actual->siguiente)->siguiente != NULL)
    {
        celda_actual = celda_actual->siguiente;
    }

    return celda_actual;
}

tPosicion l_fin(tLista lista)
{
    tPosicion toRet = lista;
    while (toRet->siguiente != NULL)
    {
        toRet = toRet->siguiente;
    }

    return toRet;
}

int l_longitud(tLista lista)
{
    int contador = 0;
    tPosicion nodo = lista;
    while (nodo->siguiente != NULL)
    {
        nodo = nodo->siguiente;
        contador++;
    }
    return contador;
}
