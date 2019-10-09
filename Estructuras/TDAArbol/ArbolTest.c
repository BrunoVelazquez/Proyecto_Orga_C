#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

void imprimir_Arbol (tArbol arbol){

    tNodo raiz= a_raiz(arbol);
    printf("Arbol: ");

    while(raiz!= NULL)

}

void imprimirRec(tArbol a,tNodo nod, tLista lista){

    tPosicion posLista= l_primera(lista);
    while (posLista!=NULL){
    tElemento elem= l_recuperar(lista,posLista);
    tNodo nodoArbol=(tNodo) elem;
    printf(nodoArbol->elemento,"  ", (nodoArbol->padre)->elemento);
    }

    imprimirRec(a,nodoArbol, nodoArbol->)
 )
}
//tkm
