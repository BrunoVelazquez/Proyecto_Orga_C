#define DEBUG_MAIN_ARBOL

#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

//Los 3 siguientes DEBUG son para los casos de rotura de codigo

//#define DEBUG_CREAR_RAIZ_YA_CREADA
//#define DEBUG_INSERTAR_DIF_PADRE
//#define DEBUG_ELIMINAR_RAIZ_CON_HIJOS


//#define DEBUG_SUBARBOL
//#define DEBUG_ELIMINAR_NORAIZ

#ifdef DEBUG_MAIN_ARBOL
void fEliminar(tElemento e)
{
    free(e);
    e = NULL;
}
void a_imprimir(tLista lista,tArbol arbol)
{
    tPosicion cursor    = l_primera(lista);
    tPosicion fin       = l_fin(lista);
    printf("LH: ");

    while (cursor != fin)
    {
        tNodo nodo = (tNodo) l_recuperar(lista,cursor);
        printf("%d ,",*(int*)a_recuperar(arbol,nodo));
        cursor = l_siguiente(lista,cursor);
    }
    printf("\n");
}


void imprimir_ArbolRec(tArbol arbol, tNodo nodo)
{
    printf("RN: %d\n", *((int*) a_recuperar(arbol,nodo)));
    tLista hijos = a_hijos(arbol,nodo);
    a_imprimir(hijos,arbol);
    tPosicion cursor = l_primera(hijos);
    tPosicion fin = l_fin(hijos);
    while (cursor != fin)
    {
        imprimir_ArbolRec(arbol,(tNodo)l_recuperar(hijos,cursor));
        cursor = l_siguiente(hijos,cursor);
    }

}

void imprimir_Arbol(tArbol arbol, int* i){
    (*i)++;
    printf("Prueba %d\n",*i);
    tNodo raiz= a_raiz(arbol);
    printf("--------------\n");
    printf("Arbol: \n");
    imprimir_ArbolRec(arbol,raiz);
    printf("--------------\n");
}

//tkm
//same

int main() {
    int contador_pruebas = 0;
    tArbol arbol;
    tNodo primer_hijo, segundo_hijo;

    int* a = (int*) malloc(sizeof(int));
    *a = 0;
    int* b = (int*) malloc(sizeof(int));
    *b = 1;
    int* c = (int*) malloc(sizeof(int));
    *c = 2;
    int* d = (int*) malloc(sizeof(int));
    *d = 3;
    int* e = (int*) malloc(sizeof(int));
    *e = 4;
    int* f = (int*) malloc(sizeof(int));
    *f = 5;
    int* g = (int*) malloc(sizeof(int));
    *g = 6;

    crear_arbol(&arbol);
    printf("Rotulo nodo = RN \nLista hijos = LH\n\n");
    crear_raiz(arbol,a);

    imprimir_Arbol(arbol,&contador_pruebas);

    //------------------------------------
    //
    //CASOS EXCEPCION
    //
    //------------------------------------

    #ifdef DEBUG_CREAR_RAIZ_YA_CREADA
    crear_raiz(arbol,a);
    #endif // DEBUG_CREAR_RAIZ_YA_CREADA

    #ifdef DEBUG_INSERTAR_DIF_PADRE //El nodo_padre parametro no es el padre del hermano pasado por parametro
    primer_hijo = a_insertar(arbol,a_raiz(arbol),NULL,b);
    a_insertar(arbol,primer_hijo,primer_hijo,c);
    imprimir_Arbol(arbol,&contador_pruebas);
    #endif // DEBUG_INSERTAR_ DIF_PADRE

    #ifdef DEBUG_ELIMINAR_RAIZ_CON_HIJOS
    primer_hijo     = a_insertar(arbol,a_raiz(arbol),NULL,b);
    segundo_hijo    = a_insertar(arbol,a_raiz(arbol),NULL,c);
    a_eliminar(arbol,a_raiz(arbol),&fEliminar);
    #endif // DEBUG_ELIMINAR_RAIZ_CON_HIJOS

    //------------------------------------
    //
    //FIN CASOS EXCEPCION
    //
    //------------------------------------


   /* tNodo nodo_b        = a_insertar(arbol,a_raiz(arbol),NULL,b);
    printf("Prueba 2\n");
    imprimir_Arbol(arbol);
    //tNodo nodo_c        = a_insertar(arbol,a_raiz(arbol),NULL,c);
    printf("Prueba 3\n");
    imprimir_Arbol(arbol);
    a_insertar(arbol,nodo_b,NULL,d);
    printf("Prueba 4\n");
    imprimir_Arbol(arbol);
    //a_insertar(arbol,a_raiz(arbol),nodo_c,f);
    printf("Prueba 4b\n");
    imprimir_Arbol(arbol);
    a_eliminar(arbol,a_raiz(arbol),&fEliminar);
    printf("Prueba eliminar raiz con un hijo\n");
    imprimir_Arbol(arbol);
    #ifdef DEBUG_ELIMINAR_NORAIZ
    a_insertar(arbol,nodo_b,NULL,e);
    printf("Prueba 5\n");
    imprimir_Arbol(arbol);
    a_eliminar(arbol,nodo_b,&fEliminar);
    printf("Prueba 6\n");

    imprimir_Arbol(arbol);
    #endif // DEBUG_ELIMINAR_NORAIZ
    #ifdef DEBUG_ELIMINAR
    a_eliminar(arbol,a_raiz(arbol),&fEliminar);
    #endif // DEBUG_ELIMINAR
    #ifdef DEBUG_SUBARBOL

    tArbol subarbol;

    a_sub_arbol(arbol,nodo_b,&subarbol);
    printf("arbol 1\n");
    imprimir_Arbol(arbol);
    printf("arbol 2\n");
    imprimir_Arbol(subarbol);

    #endif // DEBUG_SUBARBOL*/
    a_destruir(&arbol,&fEliminar);

    return 0;
}

#endif // DEBUG_MAIN_ARBOL
