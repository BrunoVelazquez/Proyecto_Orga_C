#include <stdio.h>
#include <lista.h>
#include <stdlib.h>

int main()
{
    tLista* lista = (tLista*) malloc(sizeof(tLista));
    crear_lista(lista);
    int a = 1;
    int b = 2;
    int c = 3;
    
    l_insertar(lista, l_primera(lista), &a);
}