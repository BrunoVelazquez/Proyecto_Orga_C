#include "lista.h"
#include <stdlib.h>

void crear_lista(tLista* l){
    (*l) = (tLista) malloc(sizeof(struct celda));
    // si *l es null hubo error!
    if (*l == NULL)
        exit(LST_ERROR_MEMORIA);
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

void l_insertar(tLista l, tPosicion p, tElemento e){
    tPosicion nodo_nuevo = (tPosicion) malloc(sizeof(struct celda));
    if (nodo_nuevo == NULL)
        exit(LST_ERROR_MEMORIA);
    
    tPosicion nodo_actual = l;
    while ((nodo_actual->siguiente != NULL) && (nodo_actual->siguiente != p))
        nodo_actual = nodo_actual->siguiente;

    nodo_nuevo->elemento = e;
    nodo_nuevo->siguiente = p; 
    nodo_actual->siguiente = nodo_nuevo;

}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){
    if (p == l_fin(l))
        exit(LST_POSICION_INVALIDA);
    
    tPosicion nodo_actual = l;
    while ((nodo_actual->siguiente != NULL) && (nodo_actual->siguiente != p))
        nodo_actual = nodo_actual->siguiente;
    
    tElemento elemento = nodo_actual->elemento;
    
}

int l_longitud(tLista l){
    int contador = 0;
    tPosicion nodo = l->siguiente;
    while (nodo != NULL)
    {
        nodo = nodo->siguiente;
        contador++;
    }
    return contador;
}
