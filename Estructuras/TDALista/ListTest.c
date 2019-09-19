#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG_ELIMINAR
//#define DEBUG_RECUPERAR
//#define DEBUG_SIGUIENTE
//#define DEBUG_ANTERIOR

void l_imprimir(tLista l)
{
    tPosicion cursor = l_primera(l);
    printf("Lista completa: ");
    while (cursor != l_fin(l))
    {
        printf("%d ,",*((int*) l_recuperar(l,cursor)));
        cursor = cursor->siguiente;
    }
    printf("\n");
}

void fEliminar(tElemento e)
{
    free(e);
    e = NULL;
}

int main() //TEST
{
    int *a = (int*) malloc(sizeof(int));
    *a = 0;
    int *b = (int*) malloc(sizeof(int));
    *b = 1;
    int *c = (int*) malloc(sizeof(int));
    *c = 2;
    tLista lista;
    crear_lista(&lista);
    l_insertar(lista, l_primera(lista),b);
    l_imprimir(lista);
    #ifdef DEBUG_ELIMINAR
    l_eliminar(lista,l_fin(lista),&fEliminar);
    #endif // DEBUG_ELIMINAR
    #ifdef DEBUG_RECUPERAR
    l_recuperar(lista,l_fin(lista));
    #endif // DEBUG_RECUPERAR
    #ifdef DEBUG_SIGUIENTE
    l_siguiente(lista,l_fin(lista));
    #endif // DEBUG_SIGUIENTE
    #ifdef DEBUG_ANTERIOR
    l_anterior(lista,l_primera(lista));
    #endif // DEBUG_ANTERIOR
    l_insertar(lista,l_siguiente(lista, l_primera(lista)),c);
    l_imprimir(lista);
    l_destruir(&lista,&fEliminar);
    return 0;
}
