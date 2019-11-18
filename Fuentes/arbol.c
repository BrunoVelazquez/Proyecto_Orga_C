#include "arbol.h"
#include <stdlib.h>

//Prototipos de funciones auxiliares

void (*fEliminarElementoNodo)(tElemento); // declaracion de un puntero arbol funcion.
void eliminarNodo(tElemento n);
void fEliminarListaNodos(tElemento e){}
tNodo crear_Nodo(tNodo padre, tElemento e);
tPosicion buscar_posicion_nodo(tNodo nodo);

void crear_arbol(tArbol * arbol)
{
    (*arbol) = (tArbol) malloc(sizeof(struct arbol));

    if (*arbol == NULL)                              //Chequear excepcion
        exit(ARB_ERROR_MEMORIA);

    (*arbol)->raiz=NULL;
}

void crear_raiz(tArbol arbol, tElemento e)
{
    if (arbol->raiz != NULL)              //Chequear excepcion
        exit(ARB_OPERACION_INVALIDA);

    arbol->raiz = crear_Nodo(NULL,e);                   //Crear nodo raiz
}

tNodo a_insertar(tArbol arbol, tNodo nodo_padre, tNodo nodo_hermano, tElemento e)
{
    tNodo nodo_nuevo = NULL;                              //declaracion de nuevo nodo
    tPosicion posicion_hermano = NULL;
    tLista hijos_padre = nodo_padre->hijos;

    if (nodo_hermano != NULL)                                       //Si nodo_hermano no es nulo
    {
        if (nodo_hermano->padre != nodo_padre)                              //Chequear excepcion
            exit(ARB_POSICION_INVALIDA);

        nodo_nuevo = crear_Nodo(nodo_padre,e);
        posicion_hermano = buscar_posicion_nodo(nodo_hermano);    //Buscar posicion de hermano en la lista
        l_insertar(hijos_padre,posicion_hermano,nodo_nuevo);                //Insertar nodo como rotulo de la lista como hermano izquierdo
    }
    else                                                            //De lo contrario (nodo_hermano es nulo)
    {
        nodo_nuevo = crear_Nodo(nodo_padre,e);                              //Crear nuevo nodo
        l_insertar(hijos_padre,l_fin(hijos_padre),nodo_nuevo);              //Insertar nodo como rotulo de la lista al final
    }

    return nodo_nuevo;
}

void a_eliminar(tArbol arbol, tNodo nodo, void (*fEliminar)(tElemento))
{
    int cant_hijos = l_longitud(nodo->hijos);
    tNodo nueva_raiz = NULL;
    tLista hermanos = NULL;
    tPosicion pos_nodo_a_eliminar  = NULL;
    tPosicion cursor = NULL;
    tPosicion fin = NULL;
    tNodo nodo_hijo = NULL;

    if (nodo == arbol->raiz)                                        //Si nodo es raiz
    {
        if (cant_hijos > 1)                                             //Chequear excepcion
            exit(ARB_OPERACION_INVALIDA);

        if (cant_hijos == 1)                                            //Si tiene un hijo
        {
            nueva_raiz = (tNodo) l_recuperar(nodo->hijos,l_primera(nodo->hijos)); //Setear unico hijo como nueva raiz
            nueva_raiz->padre = NULL;
            arbol->raiz = nueva_raiz;

        }
    }
    else                                                            //De lo contrario (No es la raiz)
    {
        hermanos = nodo->padre->hijos;
        pos_nodo_a_eliminar = buscar_posicion_nodo(nodo);

        cursor = l_primera(nodo->hijos);
        fin = l_fin(nodo->hijos);

        while (cursor != fin)                                                   //Sube la los hijos del nodo a eliminar como hijos del padre
        {                                                                       //del nodo a eliminar
            nodo_hijo = l_recuperar(nodo->hijos,cursor);
            nodo_hijo->padre = nodo->padre;                                     //Chequear eliminacion de lita de hijos de nodo a eliminar
            l_insertar(hermanos,pos_nodo_a_eliminar, nodo_hijo);

            pos_nodo_a_eliminar = l_siguiente(hermanos,pos_nodo_a_eliminar);
            cursor = l_siguiente(nodo->hijos,cursor);
        }

        l_eliminar(hermanos,pos_nodo_a_eliminar,&fEliminarListaNodos);

    }

    fEliminar(nodo->elemento);                                                  //Eliminar nodo
    l_destruir(&nodo->hijos,&fEliminarListaNodos);                              //Chequear eliminacion de nodo y rotulo para minmax

    nodo->padre     = NULL;                                                     //Chequear no perder elemento
    nodo->elemento  = NULL;
    free(nodo);

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

void a_destruir(tArbol * arbol, void (*fEliminar)(tElemento))
{
    tNodo nodo_aux= (*arbol)->raiz;

    fEliminarElementoNodo = fEliminar;
    eliminarNodo(nodo_aux);                                             //Eliminar nodo raiz
    fEliminarElementoNodo = NULL;

    (*arbol)->raiz=NULL;
    free(*arbol);
    *arbol=NULL;
}


void a_sub_arbol(tArbol arbol, tNodo nodo, tArbol * sa)
{
    tLista hermanos = NULL;
    tPosicion posicion_nodo_subraiz = NULL;

    (*sa) = (tArbol) malloc(sizeof(struct arbol));                      //Crear subarbol

    if (*sa == NULL)
        exit(ARB_ERROR_MEMORIA);

    hermanos = nodo->padre->hijos;                               //Buscar hermanos de nueva subraiz
    posicion_nodo_subraiz = buscar_posicion_nodo(nodo);       //Buscar posicion de nueva subraiz en lista de hermanos

    (*sa)->raiz = nodo;                                                 //Setear nueva subraiz
    nodo->padre = NULL;
    l_eliminar(hermanos,posicion_nodo_subraiz,&fEliminarListaNodos);    //Eliminar posicion de subraiz de lista de hermanos

}


/**
 * METODOS PRIVADOS
 */



/** \brief Elimina el nodo y sus referencias al padre, lista completa de hijos y elemento
 *
 * \param n = nodo a eliminar
 * \return void
 *
 */

void eliminarNodo(tElemento n)
{
    tNodo nodo= (tNodo) n;

    l_destruir(&nodo->hijos, &eliminarNodo);    //Destruir lista de hijos del nodo
    fEliminarElementoNodo(nodo->elemento);      //Liberar elemento

    nodo->padre     = NULL;                     //Setear nulos
    nodo->elemento  = NULL;
    free(nodo);
}

/** \brief Crea un tNodo con referencia a un padre y un elemento
 *
 * \param padre = nodo padre
 * \param e = elemento de nodo
 * \return nodo creado
 *
 */


tNodo crear_Nodo(tNodo padre, tElemento e)
{
    tNodo nodo_nuevo = (tNodo) malloc(sizeof(struct nodo));                 //Nodo arbol crear
    if (nodo_nuevo == NULL)
        exit(ARB_ERROR_MEMORIA);

    nodo_nuevo->elemento    = e;                                            //Setear elemento
    nodo_nuevo->padre       = padre;                                        //Setear padre
    crear_lista(&(nodo_nuevo->hijos));                                      //Inicializar lista_hijos de hijos

    return nodo_nuevo;
}

/** \brief Busca la posicion del nodo en la lista que pertenece
 *
 * \param nodo = elemento a buscar en la lista de hijos
 * \return posicion en la lista con elemento nodo pasado por parametro
 *
 */


tPosicion buscar_posicion_nodo(tNodo nodo)
{
    tLista lista_hijos = nodo->padre->hijos;
    tPosicion posicion_a_retornar = l_primera(lista_hijos);
    tPosicion pos_fin = l_fin(lista_hijos);
    int encontre = 0;

    while ((!encontre) && (posicion_a_retornar != pos_fin))                 // Mientras no llegue al fin de la lista y no encontre la posicion
    {
        if ((tNodo)l_recuperar(lista_hijos,posicion_a_retornar) == nodo)        //Si encuentro la posicion con el nodo
        {
            encontre = 1;                                                           //Encontre
        }
        else
        {
            posicion_a_retornar = l_siguiente(lista_hijos,posicion_a_retornar); //De lo contrario
        }                                                                           //Avanzar en la lista
    }
    return posicion_a_retornar;
}
