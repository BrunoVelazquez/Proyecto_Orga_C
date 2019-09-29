#include "arbol.h"
#include <stdlib.h>

void fEliminar(tElemento e);

void crear_arbol(tArbol * arbol)
{
    (*arbol) = (tArbol) malloc(sizeof(struct arbol));
    if (arbol == NULL)
        exit(ARB_ERROR_MEMORIA);
}

void crear_raiz(tArbol arbol, tElemento e)
{
    tNodo nodo_raiz = arbol->raiz;

    if (nodo_raiz != NULL)                              //Chequear excepcion
        exit(ARB_OPERACION_INVALIDA);

    nodo_raiz = (tNodo) malloc(sizeof(struct nodo));    //Crear nodo nuevo

    if (nodo_raiz == NULL)                              //Chequear memoria
        exit(ARB_ERROR_MEMORIA);

    nodo_raiz->elemento = e;                            //Setear elemento
    nodo_raiz->padre    = NULL;                         //Setear como 'raiz'
    crear_lista(&(nodo_raiz->hijos));                   //Inicializar lista de hijos
}

tNodo a_insertar(tArbol arbol, tNodo nodo_padre, tNodo nodo_hermano, tElemento e)
{
    if (nodo_hermano->padre != nodo_padre)                  //Chequear NH tiene como padre a NP
        exit(ARB_POSICION_INVALIDA);

    tNodo nodo_nuevo = (tNodo) malloc(sizeof(struct nodo)); //Nodo a crear
    if (nodo_nuevo == NULL)
        exit(ARB_ERROR_MEMORIA);

    nodo_nuevo->elemento    = e;                            //Setear elemento
    nodo_nuevo->padre       = nodo_padre;                   //Setear padre
    tLista lista_hijos_nn;
    crear_lista(&lista_hijos_nn);                           //Inicializar lista de hijos
    nodo_nuevo->hijos = lista_hijos_nn;                     //Setear lista de hijos
    
    l_insertar(nodo_padre->hijos,nodo_hermano,e);           //Preguntar
    return nodo_nuevo;
}

void a_eliminar(tArbol arbol, tNodo nodo, void (*fEliminar)(tElemento))
{
    int cant_hijos = l_longitud(nodo->hijos);

    if ((nodo == arbol->raiz) && (cant_hijos > 1)) //Chequear excepcion
        exit(ARB_OPERACION_INVALIDA);

    if ((nodo == arbol->raiz) && (cant_hijos == 1))
    {
        tNodo nueva_raiz = l_primera(nodo->hijos);
        fEliminar(nodo->elemento);
        free(nodo);
        nodo = NULL;
        arbol->raiz = nueva_raiz;
    }

    if ((nodo != arbol->raiz) && (cant_hijos > 1))
    {
        tNodo padre = nodo->padre;
        
    }
    
    
    
}

tElemento a_recuperar(tArbol arbol, tNodo nodo)
{
    return nodo->elemento;
}

tNodo a_raiz(tArbol arbol)
{
    return arbol->raiz;
}

tLista a_hijos(tArbol arbol, tNodo nodo)
{
    return nodo->hijos;
}
