#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this =(LinkedList*)malloc(sizeof(LinkedList));

    if(this != NULL)
    {
        this->pFirstNode = NULL;
        this->size = 0;
    }

    return this;
}
/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    int tam = ll_len(this);
    Node* pNodo = NULL;

    if(this != NULL && nodeIndex >= 0 && nodeIndex < tam)
    {
        pNodo = this->pFirstNode; // Apunto al primer nodo

        while(nodeIndex > 0)
        {
            pNodo = pNodo->pNextNode; // De ser mayor a 0, Recasto la direccion de memoria del nodo siguiente
            nodeIndex--;
        }
    }
    return pNodo;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int tam = ll_len(this);
    Node* nuevoNodo = NULL;

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= tam)
    {
        nuevoNodo = (Node*)malloc(sizeof(Node));
        if(nuevoNodo != NULL)
        {
            nuevoNodo->pElement = pElement; //Cargo en el nuevo nodo

            if(nodeIndex == 0)
            {
                nuevoNodo->pNextNode = this->pFirstNode;
                this->pFirstNode = nuevoNodo; //Engancho a la locomotora
            }
            else
            {
                nuevoNodo->pNextNode = getNode(this,nodeIndex);
                (getNode(this,nodeIndex-1))->pNextNode = nuevoNodo;
            }
            this->size++;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int tam = ll_len(this);

    if(this != NULL)
    {
        returnAux = addNode(this,tam,pElement); //Le paso la informacion a addNode para que inserte un nuevo nodo al final de la lista
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    int tam = ll_len(this);
    Node* auxNodo = NULL;

    if(this != NULL && index >= 0 && index < tam)
    {
        auxNodo = getNode(this,index);

        if(auxNodo != NULL)
        {
            returnAux = auxNodo->pElement;
        }
    }

    return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    int tam = ll_len(this);
    Node* auxNodo = NULL;

    if(this != NULL && index >= 0 && index < tam)
    {
        auxNodo = getNode(this,index); //Obtengo la direccion de memoria del nodo que deseo sobreescribir

        if(auxNodo != NULL)
        {
            auxNodo->pElement = pElement; // Cargo el elemento recibido como parametro, en el campo pElement del nodo obtenido
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int tam = ll_len(this);
    Node* auxNodo =  NULL;
    Node* nodoAnterior = NULL;

    if(this != NULL && index >= 0 && index < tam)
    {
        if(index == 0)
        {
            auxNodo = this->pFirstNode;
            this->pFirstNode = auxNodo->pNextNode;
        }
        else
        {
            nodoAnterior = getNode(this,index-1);
            if(nodoAnterior != NULL)
            {
                auxNodo = nodoAnterior->pNextNode;
                nodoAnterior->pNextNode = auxNodo->pNextNode;
            }
        }
        free(auxNodo);
        this->size--;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int tam = ll_len(this); // Solicito el tama�o actual de la lista

    if(this != NULL)
    {
        while( tam > 0)
        {
            ll_remove(this,0); // Comenzamos a borrar desde el principio de la lista, hasta que el tama�o de la lista sea 0
            tam--;
        }
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        ll_clear(this);
        free(this);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    int tam = ll_len(this);
    Node* auxNodo = NULL;

    if(this != NULL)
    {
        for(i = 0; i < tam; i++)
        {
            auxNodo = getNode(this,i);
            if(auxNodo != NULL && auxNodo->pElement == pElement)
            {
                returnAux = i;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int tam = ll_len(this);

    if(this != NULL)
    {
        returnAux = tam == 0 ? 1 : 0;
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    return addNode(this,index,pElement);
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = ll_get(this,index);
    ll_remove(this,index);

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = ll_indexOf(this,pElement) == -1 ? 0 : 1;
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    int tam = ll_len(this2);
    void* aux = NULL;

    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;
        for(i = 0; i < tam; i++)
        {
            aux = ll_get(this2,i);
            returnAux = ll_contains(this,aux);

            if(returnAux == 0)
            {
                break;
            }
            else
            {
                returnAux = 1;
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int tam = ll_len(this);
    int i;

    if((this != NULL) && (from < to) && (from >= 0) && (from < tam) && (to > 0) && (to <= tam))
    {
        cloneArray = ll_newLinkedList(); // Creo una nueva instancia

        if(cloneArray != NULL)
        {
            // Itero dentro del rango seleccionado
            for(i = from; i < to; i++)
            {
                ll_add(cloneArray,(ll_get(this,i))); //Agego los elementos obtenidos por el get a la nueva LinkedList
            }
        }
    }

    return cloneArray;

}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int tam = ll_len(this);

    if(this != NULL)
    {
        cloneArray = ll_subList(this,0,tam); // Copia la lista desde el primer elemento hasta el tama�o maximo de la lista
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int i;
    int j;
    int tam;
    void* auxUno = NULL;
    void* auxDos = NULL;
    void* auxTres = NULL;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
        tam = ll_len(this); // Consigo el tama�o de la lista
        for(i = 0; i < tam; i++)
        {
            auxUno = ll_get(this,i); // Me traigo el primer elemento a comparar

            for(j = i + 1; j < tam; j++)
            {
                auxDos = ll_get(this,j); //Traigo el segundo elemento a comparar

                if((order == 1) && pFunc(auxUno,auxDos) == 1) // Si es Ascendente y el segundo es menor al primero
                {
                    auxTres = auxUno;
                    auxUno = auxDos;
                    auxDos = auxTres;
                }
                else if((order == 0) && pFunc(auxUno,auxDos) == -1) // Si es Descendente y el segundo es mayor al primero
                {
                    auxTres = auxUno;
                    auxUno = auxDos;
                    auxDos = auxTres;
                }

                /* Actualizo mi lista con los cambios */
                ll_set(this,i,auxUno);
                ll_set(this,j,auxDos);
            }

        }
        returnAux = 0;
    }
    return returnAux;
}
LinkedList* ll_filterTipo(LinkedList* this, int(*pFunc)(void*,char*),char* tipo)
{
    int i;
    int tam = ll_len(this);
    void* aux;
    LinkedList* Lista = NULL;

    if(this != NULL)
    {
        Lista = ll_newLinkedList();

        if(Lista != NULL)
        {
            for(i = 0; i < tam; i++)
            {
                aux = ll_get(this,i);

                if(aux != NULL && !pFunc(aux,tipo))
                {
                    ll_add(Lista,aux);
                }
            }
        }
    }
    return Lista;
}
LinkedList* ll_map(LinkedList* this, void*(pFunc)(void* element))
{
    int i;
    int tam = ll_len(this);
    void* aux;
    LinkedList* nuevaLista = NULL;

    if(this != NULL)
    {
        nuevaLista = ll_newLinkedList();

        if(nuevaLista != NULL)
        {
            for(i = 0; i < tam; i++)
            {
                aux = ll_get(this,i);

                if(aux != NULL)
                {
                    aux = pFunc(aux);
                    ll_add(nuevaLista,aux);
                }
            }
        }
    }
    return nuevaLista;
}
