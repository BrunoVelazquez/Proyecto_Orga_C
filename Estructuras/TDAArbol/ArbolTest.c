#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG_IMPRIMIR

void fEliminar(tElemento e)
{
    free(e);
    e = NULL;
}
void l_imprimir(tLista lista,tArbol arbol)
{
    tPosicion cursor    = l_primera(lista);
    tPosicion fin       = l_fin(lista);
    printf("Lista completa: ");

    while (cursor != fin)
    {
        tNodo nodo = (tNodo) l_recuperar(lista,cursor);
        printf("%d ,",*(int*)a_recuperar(arbol,nodo));
        cursor = l_siguiente(lista,cursor);
    }
    printf("\n");
}


void imprimir_ArbolDos(tArbol arbol, tNodo nodo)
{
    printf("Rotulo nodo: %d\n", *((int*) a_recuperar(arbol,nodo)));
    tLista hijos = a_hijos(arbol,nodo);
    #ifdef DEBUG_IMPRIMIR
    printf("1");
    #endif // DEBUG_IMPRIMIR
    l_imprimir(hijos,arbol);
    #ifdef DEBUG_IMPRIMIR
    printf("2");
    #endif // DEBUG_IMPRIMIR
    tPosicion cursor = l_primera(hijos);
    tPosicion fin = l_fin(hijos);
    while (cursor != fin)
    {
        imprimir_ArbolDos(arbol,(tNodo)l_recuperar(hijos,cursor));
        cursor = l_siguiente(hijos,cursor);
    }

}

void imprimir_Arbol (tArbol arbol){

    tNodo raiz= a_raiz(arbol);
    printf("--------------\n");
    printf("Arbol: \n");

    imprimir_ArbolDos(arbol,raiz);
    printf("--------------\n");
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
    *c = 2;
    int* d = (int*) malloc(sizeof(int));
    *d = 3;
    crear_arbol(&arbol);

    crear_raiz(arbol,a);
    printf("Prueba 1\n");
    imprimir_Arbol(arbol);

    tNodo nodo_b        = a_insertar(arbol,a_raiz(arbol),NULL,b);
    printf("Prueba 2\n");
    imprimir_Arbol(arbol);
    tNodo nodo_c        = a_insertar(arbol,a_raiz(arbol),NULL,c);
    printf("Prueba 3\n");
    imprimir_Arbol(arbol);
    tNodo nodo_hijo_b   = a_insertar(arbol,nodo_b,NULL,d);
    printf("Prueba 4\n");
    imprimir_Arbol(arbol);

    tArbol subarbol;

    a_sub_arbol(arbol,nodo_b,&subarbol);
    printf("arbol 1\n");
    imprimir_Arbol(arbol);
    printf("arbol 2\n");
    imprimir_Arbol(subarbol);

    a_destruir(&arbol,&fEliminar);

    return 0;
}

