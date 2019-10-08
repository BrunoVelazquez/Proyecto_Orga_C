#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

void l_imprimir(tLista lista)
{
    tPosicion cursor = l_primera(lista);
    printf("Lista completa: ");
    while (cursor->siguiente != NULL)
    {
        printf("%d ,",*((int*) l_recuperar(lista,cursor)));
        cursor = cursor->siguiente;
    }

}


void imprimir_ArbolDos(tArbol arbol, tNodo nodo)
{
    printf("Rotulo nodo: %d\n", *((int*) a_recuperar(arbol,nodo)));
    tLista hijos = a_hijos(arbol,nodo);

}

void imprimir_Arbol (tArbol arbol){

    tNodo raiz= a_raiz(arbol);
    printf("Arbol: ");

   // imprimir_ArbolDos(arbol,raiz);
}

//tkm
//same

int main() {

    tArbol arbol;
    int* a = (int*) malloc(sizeof(int));
    *a = 0;
    int* b = (int*) malloc(sizeof(int));
    *b = 1;
    int* c = (int*) malloc(sizeof(int));
    *c = 3;
    crear_arbol(&arbol);
    crear_raiz(arbol,a);
    a_insertar(arbol,a_raiz(arbol),NULL,b);
    imprimir_Arbol(arbol);

    return 0;
}
