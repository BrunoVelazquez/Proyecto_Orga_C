#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void l_imprimir(tLista l)
{
    tPosicion pos = l->siguiente;
    printf("Lista completa: ");
    while (pos != NULL)
    {
        printf("%d , ", *(int *)pos->elemento);
        pos = pos->siguiente;
    }
    printf("\n");
}

void fEliminar(tElemento e)
{
    free(e);
    e = NULL;
}

int main()
{
    int *a = (int*) malloc(sizeof(int));
    *a = 1;
    int *b = (int*) malloc(sizeof(int));
    *b = 2;
    int *c = (int*) malloc(sizeof(int));
    *c = 3;
    tLista lista = (tLista) malloc(sizeof(struct celda));
    crear_lista(&lista);
    l_imprimir(lista);
    l_insertar(lista, l_primera(lista),b);
    l_imprimir(lista);
    l_eliminar(lista, l_primera(lista),&fEliminar);
    l_imprimir(lista);
    l_insertar(lista, l_primera(lista),c);
    l_imprimir(lista);
    /*l_insertar(lista,l_siguiente(lista, l_primera(lista)),c);
    l_imprimir(lista);
    int* d = (int*) l_recuperar(lista,l_ultima(lista));
    printf("%d\n",*d);
    l_imprimir(lista);*/
    return 0;
}
