#include "lista.h"
#include <stdlib.h>

void crear_lista(tLista* l){

    l = (tLista) malloc(sizeof(struct celda));
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;

}

void l_insertar(tLista l, tPosicion p, tElemento e){



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
