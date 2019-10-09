/*#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG_ELIMINAR
//#define DEBUG_RECUPERAR
//#define DEBUG_SIGUIENTE
//#define DEBUG_ANTERIOR

void l_imprimir(tLista lista)
{
    tPosicion cursor = l_primera(lista);
    printf("Lista completa: ");
    while (cursor->siguiente != NULL)
    {
        printf("%d ,",*((int*) l_recuperar(lista,cursor)));
        cursor = cursor->siguiente;
    }
    printf("\nLongitud lista: %d\n", l_longitud(lista));
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
    l_insertar(lista, l_primera(lista),a);
    l_insertar(lista, l_fin(lista),b);
    l_insertar(lista, l_ultima(lista),c);
    l_imprimir(lista);
    #ifdef DEBUG_ELIMINAR
    l_eliminar(lista,l_primera(lista),&fEliminar);
    l_eliminar(lista,l_ultima(lista),&fEliminar);
    l_imprimir(lista);
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

    l_destruir(&lista,&fEliminar);
    return 0;
}
*/
